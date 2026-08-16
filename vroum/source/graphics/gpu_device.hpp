#pragma once

#include "vv_headers.hpp"
#include "window/window_system.hpp"
#include "graphics/gl/vertex_array.hpp"
#include "graphics/gl/shader.hpp"
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

    Handle<VertexArray> create_vertex_array(
        const VertexBufferDesc        &vbo_1_desc,
        const BufferData              &vbo_1_data,
        const Opt<VertexBufferDesc>   &vbo_2_desc,
        const Opt<BufferData>         &vbo_2_data,
        const Opt<IndexBufferIntType> &index_buffer_int_size,
        const Opt<BufferData>         &index_buffer_data
    );
    void destroy_vertex_array(const Handle<VertexArray> &hdl);

    Handle<Shader> create_shader(
        const std::string &vs_source,
        const std::string &fs_source
    );
    void destroy_shader(const Handle<Shader> &hdl);

private:
    struct InternalState;
    Box<InternalState> m_state;

    SlotMap<VertexArray> m_vertex_arrays;
    SlotMap<Shader> m_shaders;
};

} // namespace vv