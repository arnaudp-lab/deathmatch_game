#pragma once

#include "vv_headers.hpp"
#include "SDL3/SDL.h"

#include <string>
#include <functional>
#include <map>

enum class MouseButton
{
	left,
	right,
	middle,
	x1,
	x2,
	none
};

using Callback = std::function< void( MouseButton ) >;

/*
class Input
{
public:
	inline bool get_key(SDL_Scancode key) { return m_keys[key]; }
	std::pair<bool, bool> get_mouse_state();

	void handle_keyup( SDL_Scancode key );
	void handle_keydown( SDL_Scancode key );
	void set_mouse_pos(int32_t x, int32_t y);
	void add_mouse_pos(int32_t x, int32_t y);
	void set_mouse_state( bool rc, bool lc );

	inline const int32_t get_mouse_x() const { return m_mouse_x; }
	inline const int32_t get_mouse_y() const { return m_mouse_y; }

	void on_click( MouseButton b );
	void add_click_callback( const Callback &f, const std::string &name );
	void remove_click_callback( const std::string &name );

private:
	std::map<SDL_Scancode, bool> m_keys;
	std::map<std::string, Callback> m_callbacks;
	std::pair<bool, bool> m_click_state;
	int32_t m_mouse_x = 0.0f, m_mouse_y = 0.0f;
};
*/


class Input
{
public:
	friend class Window;

	std::pair<bool, bool> get_mouse_state() const { return m_click_state; }
	bool is_keyup(const SDL_Scancode& key) const;
	int32_t mouse_x() const { return m_mouse_x; }
	int32_t mouse_y() const { return m_mouse_y; }
	int32_t mouse_dx() const { return m_mouse_dx; }
	int32_t mouse_dy() const { return m_mouse_dy; }

	void add_click_callback(const Callback& f, const std::string& name);
	void remove_click_callback(const std::string& name);
private:
	static MouseButton button_from_sdl_enum(uint8_t sdl_enum);
	void handle_keydown(SDL_Scancode key);
	void handle_keyup(SDL_Scancode key);
	void update_mouse_position(int32_t x, int32_t y, int32_t dx, int32_t dy)
	{
		m_mouse_x = x;
		m_mouse_y = y;
		m_mouse_dx = dx;
		m_mouse_dy = dy;
	}

	void dispatch_click_event(MouseButton b);

	std::map<SDL_Scancode, bool> m_keys;
	std::map<std::string, Callback> m_callbacks;
	std::pair<bool, bool> m_click_state;
	int32_t m_mouse_x = 0;
	int32_t m_mouse_y = 0;
	int32_t m_mouse_dx = 0;
	int32_t m_mouse_dy = 0;
};