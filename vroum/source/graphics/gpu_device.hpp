#pragma once

#include "vv_headers.hpp"
#include "window/window_system.hpp"
#include "graphics/gl/vertex_array.hpp"
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

private:
    struct InternalState;
    Box<InternalState> m_state;

    SlotMap<VertexArray> m_vertex_arrays;
};

} // namespace vv