#pragma once

#include "vvtypes.hpp"
#include <vector>

enum class LayoutDataType
{
	FLOAT, INT, UINT
};

struct LayoutDescription
{
	LayoutDescription(
		uint32_t location,
		uint32_t count,
		uint32_t offset,
		uint32_t stride,
		LayoutDataType type,
		bool per_instance = false):
		location(location), count(count), offset(offset), stride(stride), type(type), per_instance(per_instance)
	{}

	uint32_t location;
	uint32_t count;
	uint32_t offset;
	uint32_t stride;
	LayoutDataType type;
	bool per_instance = false;
};

class IndexBuffer
{
public:
	friend class VertexArray;

	IndexBuffer( const uint32_t *indices, size_t count );
	~IndexBuffer();

	void bind() const;
	void unbind() const;

private:
	uint32_t m_id = 0;
};

class VertexBuffer
{
public:
	friend class VertexArray;

	VertexBuffer( const void *vertices_data, size_t size );
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	uint32_t m_id = 0;
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void set_index_buffer( const Ref<IndexBuffer> &index_buffer );
	void add_vertex_buffer( const Ref<VertexBuffer> &vertex_buffer, const std::vector<LayoutDescription> &layout );

	void bind() const;
	void unbind() const;
	
private:
	Ref<IndexBuffer> m_index_buffer = nullptr;
	std::vector< Ref<VertexBuffer> > m_buffers;
	uint32_t m_id = 0;
};