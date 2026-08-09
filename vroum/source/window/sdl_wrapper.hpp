#pragma once

#include "events.hpp"
#include <SDL3/SDL_scancode.h>

namespace vv
{

Key sdl_scancode_to_key( SDL_Scancode sc );

MouseButton sdl_button_to_mouse_button( u8 sdl_button );

} // namespace vv