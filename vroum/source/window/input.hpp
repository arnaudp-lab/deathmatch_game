#pragma once

#include "vv_headers.hpp"
#include "events.hpp"

#include <array>

namespace vv
{

class Input
{
public:
	friend class WindowSystem;

	bool is_key_down(const Key& key) const
	{
		return m_keys[static_cast<size_t>(key)];
	}

	bool is_button_down(const MouseButton& btn) const
	{
		return m_buttons[static_cast<size_t>(btn)];
	};

	f32 mouse_x() const { return m_mouse_x; }
	f32 mouse_y() const { return m_mouse_y; }

	f32 mouse_dx() const { return m_mouse_dx; }
	f32 mouse_dy() const { return m_mouse_dy; }

	f32 mouse_scroll_dx() const { return m_mouse_scroll_dx; }
	f32 mouse_scroll_dy() const { return m_mouse_scroll_dy; }

private:
	void reset_mouse_movements();

	void handle_keydown(Key key);

	void handle_keyup(Key key);

	void handle_mouse_move( f32 x, f32 y, f32 dx, f32 dy );

	void handle_mouse_scroll( f32 x, f32 y );

	void handle_mouse_button_up( MouseButton btn );

	void handle_mouse_button_down( MouseButton btn );

	std::array< bool, static_cast<size_t>(Key::count) > m_keys {};
	std::array< bool, static_cast<size_t>(MouseButton::count) > m_buttons {};

	f32 m_mouse_x = 0.0f;
	f32 m_mouse_y = 0.0f;

	f32 m_mouse_dx = 0.0f;
	f32 m_mouse_dy = 0.0f;

	f32 m_mouse_scroll_dx = 0.0f;
	f32 m_mouse_scroll_dy = 0.0f;
};

} // namespace vv