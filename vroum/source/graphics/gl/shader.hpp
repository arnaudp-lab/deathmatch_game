#pragma once

#include "vv_headers.hpp"
#include <string>

namespace vv
{

struct Shader
{
	u32 id = 0;
};

Res<Shader> _create_shader(
	const std::string &vs_source,
	const std::string &fs_source
);

void _destroy_shader(const Shader &shader);

} // namespace vv