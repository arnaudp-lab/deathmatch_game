#include "core/engine_parameters.hpp"
#include "window_system.hpp"

#include "SDL3/SDL_video.h"
#include "core/logger.hpp"
#include "vv_headers.hpp"
#include <glad/glad.h>

namespace vv
{

struct WindowSystem::InternalState
{
	SDL_Window *window = nullptr;
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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
		return Error::os_window_creation_failed;
	}

	SDL_SetWindowFullscreen( m_state->window, false );

	return Error::ok;
}

void WindowSystem::shutdown()
{
	VV_DEBUG("Shutting down window");
	SDL_DestroyWindow(m_state->window);
	SDL_Quit();
}

void WindowSystem::poll_events()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_EVENT_QUIT)
		{
			m_should_close = true;
		}
	}
}

} // namespace vv