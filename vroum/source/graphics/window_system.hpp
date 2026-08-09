#pragma once

#include "vv_headers.hpp"
#include "input.hpp"
#include "core/engine_parameters.hpp"

struct SDL_Window;

namespace vv
{

class WindowSystem
{
public:
	WindowSystem();
	~WindowSystem();
	
	Error init( const EngineParameters & parameters );
	void shutdown();

	SDL_Window *get_window_handle();

	bool should_close() const { return m_should_close; }
	void poll_events();
	Input &get_input() { return m_input; }
	void resize( u32 width, u32 height );

private:
	void make_context_current();
	void swap_buffers();

	bool m_valid = false;
	bool m_should_close = false;

	Input m_input;

	struct InternalState;
	Box<InternalState> m_state;
};

} // namespace vv