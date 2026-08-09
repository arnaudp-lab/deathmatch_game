#include "engine.hpp"
#include "core/logger.hpp"
#include "graphics/render_cmd.hpp"

#include <chrono>
#include <thread>

using namespace vv;
using dseconds = std::chrono::duration<double, std::ratio<1,1>>;

Engine::Engine( const EngineParameters &params ):
	m_params(params)
{
}

Engine::~Engine()
{
}

void Engine::run()
{
	auto current_time = std::chrono::steady_clock::now();
	double target_dt = 1.0 / (float)m_params.fps;
	double current_dt = target_dt; // special case for the first dt
	double dt_max = 4.0 * target_dt;

	while(m_running)
	{
		auto previous_time = current_time;

		// Dispatch Events
		m_window_sys.poll_events();

		// Game update
		for(auto &layer: m_layers)
		{
			layer->update( current_dt );
		}

		// Rendering
		// TODO: NON ! Chaque layer va définir sa pipeline et on va juste lancer un job pour appliquer la pipeline
		for(auto &layer: m_layers)
		{
			layer->render( current_dt );
		}

		// Swap buffers
		RenderCmd cmd (RenderCmdType::swap_buffers, SwapBuffers());
		m_graphics_sys.send_render_command(cmd);

		// Check if we should still be running
		m_running = !m_window_sys.should_close();

		// Tick update
		current_time = std::chrono::steady_clock::now();
		auto frame_time = current_time - previous_time;
		double delta_time_seconds = dseconds(frame_time).count();
		if( delta_time_seconds < target_dt) {
			// wait until the delta time is target_dt
			std::this_thread::sleep_for( dseconds(target_dt - delta_time_seconds) );
		}

		current_dt = (delta_time_seconds < target_dt) ? target_dt : ((delta_time_seconds > dt_max) ? dt_max : delta_time_seconds);
	}
}

Error Engine::init_systems()
{
	Error err;

	err = m_window_sys.init( m_params );
	if( err != Error::ok )
	{
		VV_ERROR("Cannot initialize SDL3");
		return err;
	}

	err = m_graphics_sys.init( &m_window_sys );
	if( err != Error::ok )
	{
		VV_ERROR("Cannot initialize The graphic system");
		shutdown_systems();
		return err;
	}

	return Error::ok;
}

void Engine::shutdown_systems()
{
	m_graphics_sys.shutdown();
	m_window_sys.shutdown();
}