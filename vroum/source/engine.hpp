#pragma once

#include "vv_headers.hpp"
#include "core/logger.hpp"
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

	template <typename LayerType>
	Error add_layer()
	{
		auto layer_ptr = std::make_unique<LayerType>();
		layer_ptr->m_app = this;
		// Todo: only for debugging, remove once the Scene / Pipeline is defined
		layer_ptr->m_rend = &m_graphics_sys;
		layer_ptr->m_win = &m_window_sys;

		Error err = layer_ptr->init();
		if( err!= Error::ok )
		{
			VV_ERROR("Could not initialize layer");
			return err;
		}

		m_layers.push_back( std::move(layer_ptr) );

		return Error::ok;
	}

	void run();

private:
	WindowSystem m_window_sys;
	RenderingSystem m_graphics_sys;

	EngineParameters m_params;

	std::vector<std::unique_ptr<Layer>> m_layers;
	bool m_running = true;
};

} // namespace vv