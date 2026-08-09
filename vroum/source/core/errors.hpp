#pragma once

#include <string>

namespace vv
{

enum class Error
{
    ok = 0,

    // window / OS
    os_sdl_init_failed,
	os_window_creation_failed,
    os_window_already_initialized,

    // GPUDevice lifecycle
    gpu_already_initialized,
    gpu_not_initialized,
    gpu_invalid_window_handle,      // WindowSystem gave back a null SDL_Window*
    gpu_context_creation_failed,    // SDL_GL_CreateContext failed
    gpu_make_current_failed,        // SDL_GL_MakeCurrent failed
    gpu_loader_init_failed,         // gladLoadGLLoader failed
    gpu_viewport_query_failed,      // SDL_GetWindowSizeInPixels failed

    // resource creation
    gpu_shader_compile_failed,
    gpu_shader_link_failed,
    gpu_texture_creation_failed,
    gpu_buffer_creation_failed,

    unknown,
};

std::string get_err_msg( Error err );

};