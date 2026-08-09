#pragma once

#include "vvtypes.hpp"

class Texture {
public:
	Texture();

	uint32_t get_id() const { return m_id; }

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	operator bool() const { return m_valid; }

protected:
	uint32_t m_id = 0;
	bool m_valid = false;
};