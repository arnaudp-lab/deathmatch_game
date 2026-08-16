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
    gpu_invalid_window_handle,         // WindowSystem gave back a null SDL_Window*
    gpu_context_creation_failed,       // SDL_GL_CreateContext failed
    gpu_make_current_failed,           // SDL_GL_MakeCurrent failed
    gpu_loader_init_failed,            // gladLoadGLLoader failed
    gpu_viewport_query_failed,         // SDL_GetWindowSizeInPixels failed

    // Openg GL errors
    // gpu_invalid_enum,                  // GL_INVALID_ENUM raised by OpenGL
    // gpu_invalid_value,                 // GL_INVALID_VALUE raised by OpenGL
    // gpu_invalid_operation,             // GL_INVALID_OPERATION raised by OpenGL
    // gpu_out_of_memory,                 // GL_OUT_OF_MEMORY raised by OpenGL
    // gpu_invalid_framebuffer_operation, // GL_INVALID_FRAMEBUFFER_OPERATION raised by OpenGL
    
    // resource creation
    gpu_shader_compile_failed,
    gpu_shader_link_failed,
    gpu_shader_creation_failed,
    gpu_texture_creation_failed,
    gpu_buffer_creation_failed,
    gpu_vertex_array_creation_failed,

    unknown,
};

std::string get_err_msg( Error err );

};