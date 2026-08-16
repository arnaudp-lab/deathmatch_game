#include "gpu_device.hpp"

#include "core/logger.hpp"
#include "graphics/gpu/gldebug.hpp"

#include <thread>
#include <SDL3/SDL_video.h>
#include <glad/glad.h>

namespace vv
{

struct GPUDevice::InternalState
{
	SDL_GLContext context = nullptr;
	SDL_Window *sdl_window = nullptr;
	std::thread::id owner_thread;
	bool initialized = false;
};

GPUDevice::GPUDevice() : m_state( std::make_unique<InternalState>() ) {  }

GPUDevice::~GPUDevice() = default;

Error GPUDevice::init( WindowSystem *sys )
{
	if( m_state->initialized )
	{
		VV_ERROR("GPUDevice already initialized");
		return Error::gpu_already_initialized;
	}

	m_state->sdl_window = sys->get_window_handle();
	if( m_state->sdl_window == nullptr )
	{
		VV_ERROR("GPUDevice::init: WindowSystem has no valid window (was it initialized first?)");
		return Error::gpu_invalid_window_handle;
	}

	m_state->owner_thread = std::this_thread::get_id();

	m_state->context = SDL_GL_CreateContext(m_state->sdl_window);

	if(m_state->context == nullptr)
	{
		VV_ERROR("Cannot create context: ", SDL_GetError());
		return Error::gpu_context_creation_failed;
	}

	if( !SDL_GL_MakeCurrent( m_state->sdl_window, m_state->context ) )
	{
		VV_ERROR("SDL_GL_MakeCurrent failed: ", SDL_GetError());
		SDL_GL_DestroyContext( m_state->context );
		m_state->context = nullptr;
		return Error::gpu_make_current_failed;
	}

	if( !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) )
	{
		VV_ERROR("Cannot initialize GLAD");
		SDL_GL_DestroyContext( m_state->context );
		m_state->context = nullptr;
		return Error::gpu_loader_init_failed;
	}

	int w_width = 0, w_height = 0;
	if (! SDL_GetWindowSizeInPixels(m_state->sdl_window, &w_width, &w_height) )
	{
		VV_ERROR("SDL_GetWindowSizeInPixels failed: ", SDL_GetError());
		return Error::gpu_viewport_query_failed;
	}

	glViewport(0, 0, w_width, w_height);

	m_state->initialized = true;

#ifndef NDEBUG
	glEnable( GL_DEBUG_OUTPUT );
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
	glDebugMessageCallback( gl_debug::gl_debug_message_callback, 0 );
#endif

	return Error::ok;
}

void GPUDevice::shutdown()
{
	if( !m_state->initialized )
	{
		VV_WARN("GPUDevice::shutdown without being initialized first ??");
		return;
	}

	SDL_GL_DestroyContext(m_state->context);
	m_state->context = nullptr;
    m_state->initialized = false;
}

void GPUDevice::swap_buffers()
{
	SDL_GL_SwapWindow(m_state->sdl_window);
}

Res<VertexArrayHandle> GPUDevice::create_vertex_array(
	const gpu::VertexBufferDesc        &vbo_1_desc,
	const gpu::BufferData              &vbo_1_data,
	const Opt<gpu::VertexBufferDesc>   &vbo_2_desc,
	const Opt<gpu::BufferData>         &vbo_2_data,
	const Opt<gpu::IndexBufferIntType> &index_buffer_int_size,
	const Opt<gpu::BufferData>         &index_buffer_data
)
{
	auto res = gpu::_create_vertex_array(vbo_1_desc, vbo_1_data, vbo_2_desc, vbo_2_data, index_buffer_int_size, index_buffer_data);

	if(!res.is_ok())
	{
		return Res<VertexArrayHandle>::fail(res.err());
	}

	VertexArrayHandle hdl = m_vertex_arrays.push( std::move(res.value()) );

	return Res<VertexArrayHandle>::ok(hdl);
}

void GPUDevice::destroy_vertex_array(const Handle<gpu::VertexArray> &hdl)
{
	auto &vao = m_vertex_arrays.get(hdl);
	gpu::_destroy_vertex_array(vao);
	m_vertex_arrays.del(hdl);
}

Res<ShaderHandle> GPUDevice::create_shader(
	const std::string &vs_source,
	const std::string &fs_source
)
{
	auto res = gpu::_create_shader(vs_source, fs_source);

	if(!res.is_ok())
	{
		return Res<ShaderHandle>::fail(res.err());
	}

	ShaderHandle hdl = m_shaders.push( std::move(res.value()) );

	return Res<ShaderHandle>::ok(hdl);
}

void GPUDevice::destroy_shader(const Handle<gpu::Shader> &hdl)
{
	auto &shader = m_shaders.get(hdl);
	gpu::_destroy_shader(shader);
	m_shaders.del(hdl);
}

} // namespace vv
	