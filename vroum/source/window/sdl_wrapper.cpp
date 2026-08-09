#include "sdl_wrapper.hpp"
#include "SDL3/SDL_mouse.h"
#include <SDL3/SDL_scancode.h>

namespace vv
{

Key sdl_scancode_to_key( SDL_Scancode sc )
{
    switch( sc )
    {
        case SDL_SCANCODE_A: return Key::a;
        case SDL_SCANCODE_B: return Key::b;
        case SDL_SCANCODE_C: return Key::c;
        case SDL_SCANCODE_D: return Key::d;
        case SDL_SCANCODE_E: return Key::e;
        case SDL_SCANCODE_F: return Key::f;
        case SDL_SCANCODE_G: return Key::g;
        case SDL_SCANCODE_H: return Key::h;
        case SDL_SCANCODE_I: return Key::i;
        case SDL_SCANCODE_J: return Key::j;
        case SDL_SCANCODE_K: return Key::k;
        case SDL_SCANCODE_L: return Key::l;
        case SDL_SCANCODE_M: return Key::m;
        case SDL_SCANCODE_N: return Key::n;
        case SDL_SCANCODE_O: return Key::o;
        case SDL_SCANCODE_P: return Key::p;
        case SDL_SCANCODE_Q: return Key::q;
        case SDL_SCANCODE_R: return Key::r;
        case SDL_SCANCODE_S: return Key::s;
        case SDL_SCANCODE_T: return Key::t;
        case SDL_SCANCODE_U: return Key::u;
        case SDL_SCANCODE_V: return Key::v;
        case SDL_SCANCODE_W: return Key::w;
        case SDL_SCANCODE_X: return Key::x;
        case SDL_SCANCODE_Y: return Key::y;
        case SDL_SCANCODE_Z: return Key::z;

        case SDL_SCANCODE_0: return Key::num_0;
        case SDL_SCANCODE_1: return Key::num_1;
        case SDL_SCANCODE_2: return Key::num_2;
        case SDL_SCANCODE_3: return Key::num_3;
        case SDL_SCANCODE_4: return Key::num_4;
        case SDL_SCANCODE_5: return Key::num_5;
        case SDL_SCANCODE_6: return Key::num_6;
        case SDL_SCANCODE_7: return Key::num_7;
        case SDL_SCANCODE_8: return Key::num_8;
        case SDL_SCANCODE_9: return Key::num_9;

        case SDL_SCANCODE_SPACE:     return Key::space;
        case SDL_SCANCODE_ESCAPE:    return Key::escape;
        case SDL_SCANCODE_RETURN:    return Key::enter;
        case SDL_SCANCODE_TAB:       return Key::tab;
        case SDL_SCANCODE_BACKSPACE: return Key::backspace;

        case SDL_SCANCODE_LSHIFT: return Key::left_shift;
        case SDL_SCANCODE_RSHIFT: return Key::right_shift;
        case SDL_SCANCODE_LCTRL:  return Key::left_ctrl;
        case SDL_SCANCODE_RCTRL:  return Key::right_ctrl;
        case SDL_SCANCODE_LALT:   return Key::left_alt;
        case SDL_SCANCODE_RALT:   return Key::right_alt;

        case SDL_SCANCODE_UP:    return Key::up;
        case SDL_SCANCODE_DOWN:  return Key::down;
        case SDL_SCANCODE_LEFT:  return Key::left;
        case SDL_SCANCODE_RIGHT: return Key::right;

        case SDL_SCANCODE_F1:  return Key::f1;
        case SDL_SCANCODE_F2:  return Key::f2;
        case SDL_SCANCODE_F3:  return Key::f3;
        case SDL_SCANCODE_F4:  return Key::f4;
        case SDL_SCANCODE_F5:  return Key::f5;
        case SDL_SCANCODE_F6:  return Key::f6;
        case SDL_SCANCODE_F7:  return Key::f7;
        case SDL_SCANCODE_F8:  return Key::f8;
        case SDL_SCANCODE_F9:  return Key::f9;
        case SDL_SCANCODE_F10: return Key::f10;
        case SDL_SCANCODE_F11: return Key::f11;
        case SDL_SCANCODE_F12: return Key::f12;

        default: return Key::unknown;
    }
}

MouseButton sdl_button_to_mouse_button( u8 sdl_button )
{
    switch( sdl_button )
    {
        case SDL_BUTTON_LEFT:   return MouseButton::left;
        case SDL_BUTTON_RIGHT:  return MouseButton::right;
        case SDL_BUTTON_MIDDLE: return MouseButton::middle;
        default: return MouseButton::unknown;
    }
}

} // namespace vv