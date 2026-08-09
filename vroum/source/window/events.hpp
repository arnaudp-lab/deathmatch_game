#pragma once
#include "vv_headers.hpp"
#include <variant>

namespace vv
{

enum class Key : u16
{
    unknown = 0,
    a, b, c, d, e, f, g, h, i, j, k, l, m,
    n, o, p, q, r, s, t, u, v, w, x, y, z,
    num_0, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9,
    space, escape, enter, tab, backspace,
    left_shift, right_shift,
    left_ctrl, right_ctrl,
    left_alt, right_alt,
    up, down, left, right,
    f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
    count
};

enum class MouseButton : u8
{
    unknown = 0,
    left, right, middle,
    count
};

enum class EventType
{
    mouse_move,
    mouse_scroll,
    mouse_click,
    key_down,
    key_up,
    window_resize
};

struct MouseMoveEvent
{
    // absolute position, window space
    f32 x, y;

    // delta since last motion event
    f32 dx, dy;
};

struct MouseScrollEvent
{
    // horizontal/vertical scroll delta
    f32 dx, dy;
};

struct MouseClickEvent
{
    MouseButton button;
    bool pressed;
    // cursor position at time of click
    f32 x, y;
};

struct KeydownEvent
{
    Key  key;
    // Is an OS key-repeat ?
    bool repeat;
};

struct KeyupEvent
{
    Key key;
};

struct WindowResizeEvent
{
    u32 width, height;
};

struct Event
{
    EventType type;
    std::variant <
        MouseMoveEvent,
        MouseScrollEvent,
        MouseClickEvent,
        KeydownEvent,
        KeyupEvent,
        WindowResizeEvent
    > data;
};

} // namespace vv