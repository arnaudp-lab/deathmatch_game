#include "gldebug.hpp"
#include "core/errors.hpp"
#include "core/logger.hpp"
#include <glad/glad.h>

namespace vv
{

namespace gl_debug
{

static bool is_ok = true;

void GLAPIENTRY gl_debug_message_callback(
    GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
    GLsizei length,
	const GLchar* message,
	const void* userParam
)
{
    if( severity == GL_DEBUG_SEVERITY_NOTIFICATION )
        return;   // don't touch is_ok & don't log

    is_ok = false;
    VV_ERROR(
        "GL CALLBACK: ", (type == GL_DEBUG_TYPE_ERROR ? "GL ERROR" : "GL WARNING"),
        " severity=", severity, " message=", message
    );
}

void gl_debug_reset_ok()
{
	is_ok = true;
}

bool gl_debug_is_ok()
{
	return is_ok;
}


} // namespace gl_debug

} // namespace vv