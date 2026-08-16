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

struct LoadShader
{
	std::string vs_path;
	std::string fs_path;
	// TODO: wrap inside Res. [ require changing the gpu_device to propagate errors ]
	std::promise<Handle<gpu::Shader>> promise;
};

using RenderCmd = std::variant<
	InitializeCmd,
	ShutdownCmd,
	LoadShader,
	SwapBuffersCmd
>;

} // namespace vv