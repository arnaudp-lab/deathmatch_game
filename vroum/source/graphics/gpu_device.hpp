#pragma once

#include "vv_headers.hpp"
#include "window/window_system.hpp"
#include "graphics/gpu/vertex_array.hpp"
#include "graphics/gpu/shader.hpp"
#include "core/slot_map.hpp"

namespace vv
{

class GPUDevice
{
public:
    GPUDevice();
    ~GPUDevice();

    Error init( WindowSystem *sys );

    void shutdown();

    void swap_buffers();

    Handle<gpu::VertexArray> create_vertex_array(
        const gpu::VertexBufferDesc        &vbo_1_desc,
        const gpu::BufferData              &vbo_1_data,
        const Opt<gpu::VertexBufferDesc>   &vbo_2_desc,
        const Opt<gpu::BufferData>         &vbo_2_data,
        const Opt<gpu::IndexBufferIntType> &index_buffer_int_size,
        const Opt<gpu::BufferData>         &index_buffer_data
    );
    void destroy_vertex_array(const Handle<gpu::VertexArray> &hdl);

    Handle<gpu::Shader> create_shader(
        const std::string &vs_source,
        const std::string &fs_source
    );
    void destroy_shader(const Handle<gpu::Shader> &hdl);

private:
    struct InternalState;
    Box<InternalState> m_state;

    SlotMap<gpu::VertexArray> m_vertex_arrays;
    SlotMap<gpu::Shader> m_shaders;
};

} // namespace vv