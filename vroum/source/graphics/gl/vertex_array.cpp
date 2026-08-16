#include "vertex_array.hpp"
#include "core/logger.hpp"
#include "vv_headers.hpp"
#include <glad/glad.h>
#include "gldebug.hpp"

namespace vv
{

static GLuint get_opengl_type( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::f32:
		return GL_FLOAT;
	case LayoutDataType::i32:
		return GL_INT;
	case LayoutDataType::u32:
		return GL_UNSIGNED_INT;
	default: break;
	}

	VV_ASSERT(false, "unknown data type");
	return 0;
}

static bool is_integer( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::f32:
		return false;
	case LayoutDataType::i32:
	case LayoutDataType::u32:
		return true;
	default: break;
	}

	VV_ASSERT(false, "unknown data type");
	return false;
} 

static uint32_t get_type_size( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::f32:
		return 4;
	case LayoutDataType::i32:
		return 4;
	case LayoutDataType::u32:
		return 4;
	default: break;
	}

	VV_ASSERT(false, "unknown data type");
	return 0;
}

static Res<u32> attach_vbo(u32 vao, u32 binding_index, const VertexBufferDesc &vbo_desc, const BufferData &vbo_data )
{
	VV_ASSERT(vbo_data.data != nullptr, "Buffer Data is nullptr in attach_vbo");
	
	u32 vbo = 0;
	glCreateBuffers(1, &vbo);
	glNamedBufferData(vbo, vbo_data.size_bytes, vbo_data.data, GL_STATIC_DRAW);
	
	int strides = vbo_desc.stride;
	GLintptr offset = 0;
	glVertexArrayVertexBuffers(
		vao, binding_index, 1, &vbo, 0, (const GLsizei*)&strides
	);

	for( const auto &lay: vbo_desc.attributes )
	{
		glEnableVertexArrayAttrib(vao, lay.location);
		
		if(is_integer(lay.type))
		{
			glVertexArrayAttribIFormat(
				vao, lay.location, lay.count, get_opengl_type(lay.type), lay.offset
			);
		}
		else
		{
			glVertexArrayAttribFormat(
				vao, lay.location, lay.count, get_opengl_type(lay.type), lay.normalized ? GL_TRUE : GL_FALSE, lay.offset
			);
		}

		glVertexArrayAttribBinding(vao, lay.location, binding_index);

		if(lay.per_instance)
			glVertexArrayBindingDivisor(vao, binding_index, 1);
		
	}

	return Res<u32>{Error::ok, vbo};
}

Res<VertexArray> _create_vertex_array(
	const VertexBufferDesc        &vbo_1_desc,
	const BufferData              &vbo_1_data,
	const Opt<VertexBufferDesc>   &vbo_2_desc,
	const Opt<BufferData>         &vbo_2_data,
	const Opt<IndexBufferIntType> &index_buffer_int_size,
	const Opt<BufferData>         &index_buffer_data
)
{
	VV_ASSERT(
		((vbo_2_data.has_value() && vbo_2_desc.has_value()) || (!vbo_2_data.has_value() && !vbo_2_desc.has_value())),
		"Invalid argument to create_vertex_array, vbo_2_desc and vbo_2_data bust be all defined or all undefied."
	);

	VV_ASSERT(
		((index_buffer_int_size.has_value() && index_buffer_data.has_value()) || (!index_buffer_int_size.has_value() && !index_buffer_data.has_value())),
		"Invalid argument to create_vertex_array, index_buffer_data and index_buffer_int_size bust be all defined or all undefied."
	);

	VertexArray res {};
	gl_debug::gl_debug_reset_ok();

	// VAO Object creation and binding into current context
	glCreateVertexArrays(1, &res.vertex_array_id);

	// First VBO - create, bind and specify layout
	auto maybe_vbo_1 = attach_vbo(res.vertex_array_id, 0, vbo_1_desc, vbo_1_data);

	if( !maybe_vbo_1.ok() )
	{
		VV_ERROR("Could not create or bind the vertex buffer");
		_destroy_vertex_array(res);
		return Res<VertexArray>{.err = maybe_vbo_1.err, .value=res};
	}

	res.vertex_buffer_1_id = maybe_vbo_1.value;

	// Second VBO - create, bind and specify layout
	if( (vbo_2_data.has_value() && (vbo_2_desc.has_value())) )
	{
		auto maybe_vbo_2 = attach_vbo(res.vertex_array_id, 1, vbo_2_desc.value(), vbo_2_data.value());

		if( !maybe_vbo_2.ok() )
		{
			VV_ERROR("Could not create or bind the vertex buffer");
			_destroy_vertex_array(res);
			return Res<VertexArray>{.err = maybe_vbo_2.err, .value=res};
		}

		res.vertex_buffer_2_id = maybe_vbo_2.value;
	}

	// Index Buffer
	if( index_buffer_int_size.has_value() && index_buffer_data.has_value() )
	{
		auto &bfr_data = index_buffer_data.value();
		glCreateBuffers(1, &res.index_buffer_id);
		glNamedBufferData(res.index_buffer_id, bfr_data.size_bytes, bfr_data.data, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(res.vertex_array_id, res.index_buffer_id);
		res.index_buffer_int_type = index_buffer_int_size.value();
	}

	if( !gl_debug::gl_debug_is_ok() )
	{
		_destroy_vertex_array(res);
		return {.err=Error::gpu_vertex_array_creation_failed, .value=res};
	}

	return {Error::ok, res};
}

void _destroy_vertex_array( VertexArray &vertex_array )
{
	glDeleteBuffers(1, &vertex_array.index_buffer_id);
	glDeleteBuffers(1, &vertex_array.vertex_buffer_1_id);
	glDeleteBuffers(1, &vertex_array.vertex_buffer_2_id);
	glDeleteVertexArrays(1, &vertex_array.vertex_array_id);
}

} // namespace vv