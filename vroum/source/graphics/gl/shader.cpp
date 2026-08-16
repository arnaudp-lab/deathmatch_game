#include "shader.hpp"

#include "gldebug.hpp"
#include "core/logger.hpp"
#include <glad/glad.h>

namespace vv
{

Res<u32> compile_shader(const std::string &source, GLuint shader_type)
{
	auto c_str_source = source.c_str();
	uint32_t shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &c_str_source, nullptr);
	glCompileShader(shader_id);

	int success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infos[512];
		glGetShaderInfoLog(shader_id, 512, nullptr, infos);
		VV_ERROR("Impossible de compiler le shader: ", infos);
		glDeleteShader(shader_id);
		return {.err = Error::gpu_shader_compile_failed, .value=0};
	}

	return {.err = Error::ok, .value=shader_id};
}

Res<Shader> _create_shader(
	const std::string &vs_source,
	const std::string &fs_source
)
{
	gl_debug::gl_debug_reset_ok();

	Shader res;
	res.id = glCreateProgram();

	auto vs = compile_shader(vs_source, GL_VERTEX_SHADER);
	auto fs = compile_shader(fs_source, GL_FRAGMENT_SHADER);

	if(!vs.ok()) return {.err = vs.err, .value=res};
	if(!fs.ok()) return {.err = fs.err, .value=res};

	res.id = glCreateProgram();
	glAttachShader(res.id, vs.value);
	glAttachShader(res.id, fs.value);
	glLinkProgram(res.id);
	glDeleteShader(vs.value);
	glDeleteShader(fs.value);

	int success;
	glGetProgramiv(res.id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[512];
		glGetProgramInfoLog(res.id, 512, nullptr, info);
		VV_ERROR("Impossible de lier les shaders: ", info);
		_destroy_shader(res);
		return {.err=Error::gpu_shader_link_failed, .value=res};
	}

	if(!gl_debug::gl_debug_is_ok())
	{
		_destroy_shader(res);
		return {.err=Error::gpu_shader_creation_failed, .value=res};
	}

	return {.err = Error::ok, .value=res};
}

void _destroy_shader(const Shader &shader)
{
	glDeleteProgram(shader.id);
}

} // namespace vv


