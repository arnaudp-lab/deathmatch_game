#include "shader.hpp"

#include "gldebug.hpp"
#include "core/logger.hpp"
#include "utils.hpp"

#include <glad/glad.h>
#include <fstream>
#include <iterator>
#include <cassert>

Shader::Shader(const std::string &vs_path, const std::string &fs_path)
{
	m_valid = load_from_file(vs_path, fs_path);
}

bool Shader::load_from_file(const std::string &vs_path, const std::string &fs_path)
{
	auto vs = compile_shader(vs_path, GL_VERTEX_SHADER);
	if( !vs ) return false;

	auto fs = compile_shader(fs_path, GL_FRAGMENT_SHADER);
	if( !fs ) return false;

	// create program and link shaders
	uint32_t shader_id = glCreateProgram();

	glAttachShader(shader_id, vs.value());

	glAttachShader(shader_id, fs.value());

	glLinkProgram(shader_id);

	// cleaning before we may return
	glDeleteShader(vs.value());
	glDeleteShader(fs.value());

	// error handling
	int success;
	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[512];
		glGetProgramInfoLog(shader_id, 512, nullptr, info);
		VV_ERROR("Impossible de lier les shaders: ", info);
		return false;
	}

	m_id = shader_id;

	return true;
}

Shader::Shader()
{
	m_valid = false;
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::bind()
{
	assert(m_valid);
	glUseProgram(m_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::set_int(const std::string& name, int value)
{
	assert(m_valid);
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value)
{
	assert(m_valid);
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, float x, float y)
{
	assert(m_valid);
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string& name, float x, float y, float z)
{
	assert(m_valid);
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string& name, float x, float y, float z, float w)
{
	assert(m_valid);
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat4(const std::string& name, float *matrix)
{
	assert(m_valid);
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, matrix);
}

Opt<uint32_t> Shader::compile_shader(const std::string& path, uint32_t type)
{
	Opt<std::string> source = vv::get_file_content( std::string{"../"} + path );

	if( !source )
	{
		VV_ERROR("Impossible de récuperer le shader: ", path );
		return {};
	}

	auto c_str_source = source.value().c_str();
	uint32_t shader = glCreateShader(type);
	glShaderSource(shader, 1, &c_str_source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infos[512];
		glGetShaderInfoLog(shader, 512, nullptr, infos);
		VV_ERROR("Impossible de compiler le shader: ", infos);
		return {};
	}

	log_gl_errors();
	return shader;
}
