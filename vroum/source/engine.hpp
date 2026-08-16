#pragma once

#include "resource_manager/resource_manager.hpp"
#include "vv_headers.hpp"
#include "layer.hpp"
#include "window/window_system.hpp"
#include "graphics/rendering_system.hpp"
#include "core/engine_parameters.hpp"

#include <SDL3/SDL.h>

#include <vector>
#include <memory>

namespace vv
{

class Engine
{
public:
	Engine( const EngineParameters &params );
	~Engine();

	Error init_systems();
	void shutdown_systems();

	Error add_layer( Box<Layer> &&layer );

	void run();

private:
	WindowSystem    m_window_sys;
	RenderingSystem m_graphics_sys;
	ResourceManager m_resource_manager;

	EngineParameters m_params;

	std::vector<std::unique_ptr<Layer>> m_layers;
	bool m_running = true;
};

} // namespace vv