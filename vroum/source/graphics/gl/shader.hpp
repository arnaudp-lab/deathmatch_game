#pragma once

#include "vvtypes.hpp"
#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string &vs_path, const std::string &fs_path);
	~Shader();

	operator bool() const { return m_valid; }

	Shader(const Shader&) = delete;
	Shader &operator=(const Shader&) = delete;

	// TODO: add load_from_file for consistency

	// TODO: put these functions in private && use [friend class Renderer;]
	void bind();
	void unbind();
	void set_int( const std::string &name, int value );
	void set_float( const std::string& name, float value);
	void set_vec2( const std::string& name, float x, float y);
	void set_vec3( const std::string& name, float x, float y, float z);
	void set_vec4( const std::string& name, float x, float y, float z, float w);
	void set_mat4( const std::string& name, float* matrix );

private:
	bool load_from_file(const std::string &vs_path, const std::string &fs_path);
	static Opt<uint32_t> compile_shader( const std::string &path, uint32_t type);

	uint32_t m_id;
	bool m_valid;
};

