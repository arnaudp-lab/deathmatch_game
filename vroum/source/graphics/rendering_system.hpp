#pragma once

#include "vv_headers.hpp"

#include "graphics/gpu_device.hpp"
#include "render_cmd.hpp"
#include "window/window_system.hpp"

#include <SDL3/SDL.h>

#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace vv
{
	
class RenderingSystem
{
public:
	RenderingSystem();

	RenderingSystem(const RenderingSystem &) = delete;
	RenderingSystem &operator=(const RenderingSystem &) = delete;

	Error init( WindowSystem *window_sys );

	void shutdown();

	void send_render_command( const RenderCmd &cmd );
	
private:
	void start_thread();

	void worker_loop();

	void execute_cmd( const RenderCmd &cmd);

	// Just call m_device.init/shutdown, used as rendercommand callback
	void init_opengl( WindowSystem *window_sys );
	void shutdown_opengl();

	// Management of the rendering thread
	std::mutex m_mtx;
	std::condition_variable m_cv;
	std::deque<RenderCmd> m_command_queue;
	std::thread m_gpu_thread;
	bool m_worker_running = true;

	// API-agnostic device, handles context + render commands to GPU
	GPUDevice m_device;
};

} // namespace vv