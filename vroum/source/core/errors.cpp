#include "core/errors.hpp"

namespace vv
{

std::string get_err_msg( Error err )
{
    switch( err )
    {
        case Error::ok:
            return "ok";

        case Error::os_window_already_initialized:
            return "WindowSystem::init called more than once";

        case Error::gpu_already_initialized:
            return "GPUDevice::init called more than once";

        case Error::gpu_not_initialized:
            return "GPUDevice used before init() succeeded";

        case Error::gpu_invalid_window_handle:
            return "WindowSystem returned a null SDL_Window* (was it initialized first?)";

        case Error::gpu_context_creation_failed:
            return "SDL_GL_CreateContext failed";

        case Error::gpu_make_current_failed:
            return "SDL_GL_MakeCurrent failed";

        case Error::gpu_loader_init_failed:
            return "GLAD failed to load GL function pointers";

        case Error::gpu_viewport_query_failed:
            return "SDL_GetWindowSizeInPixels failed";

        case Error::gpu_shader_compile_failed:
            return "shader compilation failed";

        case Error::gpu_shader_link_failed:
            return "shader program linking failed";

        case Error::gpu_texture_creation_failed:
            return "texture creation failed";
            
        case Error::gpu_buffer_creation_failed:
            return "GPU buffer creation failed";

        case Error::unknown:
            return "unknown error";
    }

    return "invalid Error value (enum/string mismatch)";
}

} // namespace vv