#pragma once

#include <glad/glad.h>

namespace vv
{

namespace gl_debug
{

void GLAPIENTRY gl_debug_message_callback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam );

void gl_debug_reset_ok();
bool gl_debug_is_ok();

} // namespace gl_debug

} // namespace vv