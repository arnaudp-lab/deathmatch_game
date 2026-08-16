#include "shader.hpp"

#include "gldebug.hpp"
#include "core/logger.hpp"
#include <glad/glad.h>

namespace vv
{

namespace gpu
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
		return Res<u32>::fail(Error::gpu_shader_compile_failed);
	}

	return Res<u32>::ok(shader_id);
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

	if(!vs.ok()) return Res<Shader>::fail(vs.err());
	if(!fs.ok()) return Res<Shader>::fail(fs.err());

	res.id = glCreateProgram();
	glAttachShader(res.id, vs.value());
	glAttachShader(res.id, fs.value());
	glLinkProgram(res.id);
	glDeleteShader(vs.value());
	glDeleteShader(fs.value());

	int success;
	glGetProgramiv(res.id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[512];
		glGetProgramInfoLog(res.id, 512, nullptr, info);
		VV_ERROR("Impossible de lier les shaders: ", info);
		_destroy_shader(res);
		return Res<Shader>::fail(Error::gpu_shader_link_failed);
	}

	if(!gl_debug::gl_debug_is_ok())
	{
		_destroy_shader(res);
		return Res<Shader>::fail(Error::gpu_shader_creation_failed);
	}

	return Res<Shader>::ok(res);
}

void _destroy_shader(const Shader &shader)
{
	glDeleteProgram(shader.id);
}

} // namespace gpu

} // namespace vv