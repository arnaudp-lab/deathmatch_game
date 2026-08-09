#pragma once

#include <variant>
#include <memory>
#include <SDL3/SDL.h>
#include "window_system.hpp"

namespace vv
{

struct InitializeCmd
{
	InitializeCmd(WindowSystem *window): window(window) {}
	InitializeCmd() = default;

	WindowSystem *window = nullptr;
};

struct ShutdownCmd
{
	// empty
};

struct SwapBuffers
{
	// empty
};

enum class RenderCmdType
{
	initialize, shutdown, swap_buffers
};

struct RenderCmd
{
	using RenderCmdVariant = std::variant<
		std::shared_ptr<InitializeCmd>,
		ShutdownCmd,
		SwapBuffers
	>;

	RenderCmd() = default;

	RenderCmd(const RenderCmdType &type, const RenderCmdVariant &data ):
		type(type), data(data) {}

	RenderCmdType type;
	RenderCmdVariant data;
};

} // namespace vv