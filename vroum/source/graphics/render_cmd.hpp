#pragma once

#include <variant>
#include <future>

#include <SDL3/SDL.h>
#include "window/window_system.hpp"
#include "gpu_device.hpp"

namespace vv
{

struct InitializeCmd
{
	WindowSystem *window = nullptr;
};

struct ShutdownCmd
{
	// empty
};

struct SwapBuffersCmd
{
	// empty
};

struct LoadShaderCmd
{
	std::string vs_source {};
	std::string fs_source {};
	std::promise<Res<ShaderHandle>> promise {};
};

struct DestroyShaderCmd
{
	ShaderHandle hdl;
};

using RenderCmd = std::variant<
	InitializeCmd,
	ShutdownCmd,
	LoadShaderCmd,
	SwapBuffersCmd,
	DestroyShaderCmd
>;

} // namespace vv