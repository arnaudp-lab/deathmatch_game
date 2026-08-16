#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "core/engine_parameters.hpp"
#include "window_system.hpp"
#include "sdl_wrapper.hpp"

#include "SDL3/SDL_video.h"
#include "core/logger.hpp"
#include "vv_headers.hpp"
#include "window/sdl_wrapper.hpp"
#include <glad/glad.h>
#include <thread>

namespace vv
{

struct WindowSystem::InternalState
{
	SDL_Window *window = nullptr;
	std::thread::id owner_thread;
	bool initialized = false;
};

// Leaky but not that bad I think
SDL_Window *WindowSystem::get_window_handle()
{
	return m_state->window;
}

WindowSystem::WindowSystem()  : m_state( std::make_unique<InternalState>() ) {}
WindowSystem::~WindowSystem() = default;

Error WindowSystem::init( const EngineParameters &params )
{
	VV_ASSERT( m_state->window == nullptr, "WindowSystem::init was called multiple times" ); // double initialization

	if (! SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS) )
	{
		VV_ERROR("Error when calling SDL_Init", SDL_GetError());
		return Error::os_sdl_init_failed;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	m_state->window = SDL_CreateWindow(
		params.window_title.c_str(),
		params.window_width,
		params.window_height,
		window_flags
	);

	if( m_state->window == nullptr ) {
		VV_ERROR("Error when calling SDL_CreateWindow: ", SDL_GetError());
		shutdown();
		return Error::os_window_creation_failed;
	}

	SDL_SetWindowFullscreen( m_state->window, false );

	m_state->owner_thread = std::this_thread::get_id();
	m_state->initialized = true;

	return Error::ok;
}

void WindowSystem::shutdown()
{
	VV_DEBUG("Shutting down window");
	SDL_DestroyWindow(m_state->window);
	SDL_Quit();
	m_state->window = nullptr;
    m_state->initialized = false;
}

std::vector<Event> WindowSystem::poll_events()
{
	m_input.reset_mouse_movements();

	std::vector<Event> event_queue;
	event_queue.reserve(16);

	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		// ==== Convert SDL_Event to internal types ====
		switch( event.type )
		{
			case SDL_EVENT_QUIT:
			{
				m_should_close = true;
				break;
			}
			
			case SDL_EVENT_KEY_DOWN:
			{
				Key vv_code = sdl_scancode_to_key( event.key.scancode );
				m_input.handle_keydown( vv_code );

				Event vv_event{ EventType::key_down, KeydownEvent{ vv_code, event.key.repeat } };
				event_queue.push_back( vv_event );
				break;
			}

			case SDL_EVENT_KEY_UP:
			{
				Key vv_code = sdl_scancode_to_key( event.key.scancode );
				m_input.handle_keyup( vv_code );   // was handle_keydown — bug fixed

				Event vv_event{ EventType::key_up, KeyupEvent{ vv_code } };
				event_queue.push_back( vv_event );
				break;
			}

			case SDL_EVENT_MOUSE_MOTION:
			{
				f32 x  = event.motion.x,  y  = event.motion.y;
				f32 dx = event.motion.xrel, dy = event.motion.yrel;
				m_input.handle_mouse_move( x, y, dx, dy );

				Event vv_event{ EventType::mouse_move, MouseMoveEvent{ x, y, dx, dy } };
				event_queue.push_back( vv_event );
				break;
			}

			case SDL_EVENT_MOUSE_WHEEL:
			{
				f32 dx = event.wheel.x, dy = event.wheel.y;
				m_input.handle_mouse_scroll( dx, dy );

				Event vv_event{ EventType::mouse_scroll, MouseScrollEvent{ dx, dy } };
				event_queue.push_back( vv_event );
				break;
			}

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				MouseButton vv_button = sdl_button_to_mouse_button( event.button.button );
				bool pressed = ( event.type == SDL_EVENT_MOUSE_BUTTON_DOWN );

				if( pressed )
					m_input.handle_mouse_button_down( vv_button );
				else
					m_input.handle_mouse_button_up( vv_button );

				Event vv_event{ EventType::mouse_click,
					MouseClickEvent{ vv_button, pressed, event.button.x, event.button.y } };
				event_queue.push_back( vv_event );
				break;
			}

			case SDL_EVENT_WINDOW_RESIZED:
			{
				// See SDL3's doc
				u32 width  = (u32)event.window.data1;
				u32 height = (u32)event.window.data2;

				Event vv_event{ EventType::window_resize, WindowResizeEvent{ width, height } };
				event_queue.push_back( vv_event );
				break;
			}

			default: break;
		}
	}

	return event_queue;
}

} // namespace vv