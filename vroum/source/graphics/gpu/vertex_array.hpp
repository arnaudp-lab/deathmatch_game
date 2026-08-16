#pragma once

#include "vv_headers.hpp"
#include <vector>

namespace vv
{

namespace gpu
{

enum class LayoutDataType
{
	f32, i32, u32, u8, u16
};

enum class IndexBufferIntType
{
	integer, short_integer
};

struct AttributeDesc
{
    u32 location;
    u32 count;
    u32 offset;
    LayoutDataType type;
	bool normalized = false;
    bool per_instance = false;
};

struct VertexBufferDesc
{
    u32 stride;
    std::vector<AttributeDesc> attributes;
};

struct VertexArray
{
	u32 vertex_buffer_1_id = 0;
	u32 vertex_buffer_2_id = 0;
	u32 vertex_array_id    = 0;
	u32 index_buffer_id    = 0;
	IndexBufferIntType index_buffer_int_type {};
};

struct BufferData
{
    const void *data = nullptr;
    u32 size_bytes = 0;
};

Res<VertexArray> _create_vertex_array(
	const VertexBufferDesc        &vbo_1_desc,
	const BufferData              &vbo_1_data,
	const Opt<VertexBufferDesc>   &vbo_2_desc,
	const Opt<BufferData>         &vbo_2_data,
	const Opt<IndexBufferIntType> &index_buffer_int_size,
	const Opt<BufferData>         &index_buffer_data
);

void _destroy_vertex_array( VertexArray &vertex_array );

} // namespace gpu

} // namespace vv