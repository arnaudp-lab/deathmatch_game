#include "input.hpp"

namespace vv
{

void Input::handle_keyup(Key key)
{
	m_keys[static_cast<size_t>(key)] = false;
}

void Input::handle_keydown(Key key)
{
	m_keys[static_cast<size_t>(key)] = true;
}

void Input::reset_mouse_movements()
{
	m_mouse_dx = 0.0f;
	m_mouse_dy = 0.0f;
	m_mouse_scroll_dx = 0.0f;
	m_mouse_scroll_dy = 0.0f;
}

void Input::handle_mouse_move( f32 x, f32 y, f32 dx, f32 dy )
{
	m_mouse_x = x;
	m_mouse_y = y;
	m_mouse_dx += dx;
	m_mouse_dy += dy;
}

void Input::handle_mouse_scroll( f32 x, f32 y )
{
	m_mouse_scroll_dx += x;
	m_mouse_scroll_dy += y;
}

void Input::handle_mouse_button_up( MouseButton btn )
{
	m_buttons[static_cast<size_t>(btn)] = false;
}

void Input::handle_mouse_button_down( MouseButton btn )
{
	m_buttons[static_cast<size_t>(btn)] = true;
}

} // namespace vv