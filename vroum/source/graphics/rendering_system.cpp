#include "core/logger.hpp"
#include "vv_headers.hpp"
#include "rendering_system.hpp"
#include <glad/glad.h>

using namespace vv;

RenderingSystem::RenderingSystem()
{

}

void RenderingSystem::start_thread()
{
	m_worker_running = true;
	m_gpu_thread = std::thread(&RenderingSystem::worker_loop, this);
}

void RenderingSystem::worker_loop()
{
	m_worker_running = true;

	while(true)
	{
		RenderCmd cmd;

		{
			// Wait for something to do
			std::unique_lock<std::mutex> lock(m_mtx);
			m_cv.wait(lock, [this]() { return !m_command_queue.empty() || !m_worker_running; });
			
			// Shutdown if necessary
			if(!m_worker_running)
			{
				VV_DEBUG("Worker loop shutdown");
				return;
			}
			
			// Get the command at the front
			cmd = m_command_queue.front();
			m_command_queue.pop_front();

		} // we now have the command, we can let other thread send messages again
		
		// Execute the command
		execute_cmd(cmd);
	}
}

void RenderingSystem::execute_cmd(const RenderCmd &cmd)
{
	switch(cmd.type)
	{
	case RenderCmdType::initialize:
		this->init_opengl(std::get< Ref<InitializeCmd> >(cmd.data)->window);
		break;
	case RenderCmdType::shutdown:
		this->shutdown_opengl();
		break;
	case RenderCmdType::swap_buffers:
		m_device.swap_buffers();
		break;
	default:
		VV_WARN("Unknown command type passed to the rendering system: ", static_cast<int>(cmd.type) );
		break;
	}
}

void RenderingSystem::send_render_command(const RenderCmd &cmd)
{
	{
		std::lock_guard<std::mutex> lock(m_mtx); 	
		m_command_queue.push_back(cmd);
	}
	m_cv.notify_one();
}

Error RenderingSystem::init( WindowSystem *window_sys )
{
	// start the rendering thread
	start_thread();

	// immediatly send a command to the opengl thread
	// that tells it to initialize opengl on its end
	RenderCmd cmd (RenderCmdType::initialize, std::make_shared<InitializeCmd>(window_sys));
	send_render_command(cmd);

	return Error::ok;
}

void RenderingSystem::shutdown()
{
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_command_queue.clear();
	}
	
	send_render_command(RenderCmd(RenderCmdType::shutdown, ShutdownCmd()));

	m_gpu_thread.join();
}

void RenderingSystem::init_opengl( WindowSystem *window_sys )
{
	Error err = m_device.init(window_sys);
	if( err != Error::ok )
	{
		VV_FATAL("Could not initialize the GPU device");
		VV_ASSERT(false, "Could not initialize GPU Device, asserted false from GPU thread [TODO: handle this differently if needed?]");
		return;
	}
}

void RenderingSystem::shutdown_opengl()
{
	m_device.shutdown();
	m_worker_running = false;
}
