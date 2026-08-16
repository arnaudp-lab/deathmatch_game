#pragma once

#include "vv_headers.hpp"
#include <string>

namespace vv
{

struct EngineParameters
{
	u32 window_width = 1920;
	u32 window_height = 1080;
	bool fps_cap = true;
	bool fullscreen = false;
	u32 fps = 30;
	float sensitivity = 0.05f;
	std::string window_title = "ECO+ Deathmatch ULTIMATE";
	std::string resources_root = "./";
};

} // namespace vv