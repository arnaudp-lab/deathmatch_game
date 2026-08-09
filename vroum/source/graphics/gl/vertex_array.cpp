#include "vertex_array.hpp"
#include "gldebug.hpp"
#include <glad/glad.h>

static GLuint get_opengl_type( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::FLOAT:
		return GL_FLOAT;
	case LayoutDataType::INT:
		return GL_INT;
	case LayoutDataType::UINT:
		return GL_UNSIGNED_INT;
	default: break;
	}

	assert(false && "unknown data type");
	return 0;
}

static bool is_integer( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::FLOAT:
		return false;
	case LayoutDataType::INT:
	case LayoutDataType::UINT:
		return true;
	default: break;
	}

	assert(false && "unknown data type");
	return false;
} 


static uint32_t get_type_size( const LayoutDataType &type )
{
	switch(type)
	{
	case LayoutDataType::FLOAT:
		return 4;
	case LayoutDataType::INT:
		return 4;
	case LayoutDataType::UINT:
		return 4;
	default: break;
	}

	assert(false && "unknown data type");
	return 0;
}

IndexBuffer::IndexBuffer( const uint32_t *indices, size_t count )
{
	assert(indices != nullptr);
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (void*)indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer( const void *vertices_data, size_t size )
{
	assert(vertices_data != nullptr);
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	log_gl_errors();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::set_index_buffer( const Ref<IndexBuffer> &index_buffer )
{
	m_index_buffer = index_buffer;
	bind();
	index_buffer->bind();
	unbind();
	index_buffer->unbind();
}

void VertexArray::add_vertex_buffer( const Ref<VertexBuffer> &vertex_buffer, const std::vector<LayoutDescription> &layout )
{
	assert(vertex_buffer); // != nullptr
	m_buffers.push_back(vertex_buffer);
	bind();
	vertex_buffer->bind();

	for( const auto &desc: layout )
	{
		glEnableVertexAttribArray(desc.location);
		
		if(is_integer(desc.type))
		{
			glVertexAttribIPointer(
				desc.location,
				desc.count,
				get_opengl_type(desc.type),
				desc.stride,
				(void*)(desc.offset)
			);
		}
		else 
		{
			glVertexAttribPointer(
				desc.location,
				desc.count,
				get_opengl_type(desc.type),
				GL_FALSE,
				desc.stride,
				(void*)(desc.offset)
			);
		}


		if(desc.per_instance)
			glVertexAttribDivisor(desc.location, 1);
		
		log_gl_errors();
	}
	unbind();
}

/*
void VertexArray::set_layout( const std::vector<LayoutDescription> &layout )
{
	bind();

	for( const auto &desc: layout )
	{
		glEnableVertexAttribArray(desc.location);
		
		if(desc.per_instance)
		{
			assert(m_instance_buffer);
			m_instance_buffer->bind();
		}
		else
		{
			assert(m_vertex_buffer);
			m_vertex_buffer->bind();
		}
		
		glVertexAttribPointer(
			desc.location,
			desc.count,
			get_opengl_type(desc.type),
			GL_FALSE,
			desc.stride,
			(void*)(desc.offset)
		);

		if(desc.per_instance)
			glVertexAttribDivisor(desc.location, 1);
	}

	unbind();
}

void VertexArray::set_instance_buffer( const Ref<VertexBuffer> &vertex_buffer )
{
	m_instance_buffer = vertex_buffer;
}

void VertexArray::set_vertex_buffer( const Ref<VertexBuffer> &vertex_buffer )
{
	m_vertex_buffer = vertex_buffer;
}*/