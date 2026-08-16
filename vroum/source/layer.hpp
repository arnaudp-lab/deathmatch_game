#pragma once

#include "window/window_system.hpp"
#include "resource_manager/resource_manager.hpp"
#include "vv_headers.hpp"

namespace vv
{

class Engine;
class RenderingSystem;

class Layer
{
public:
	friend class Engine;

	virtual ~Layer() {}

	virtual Error init() = 0;

	virtual void shutdown() = 0;

	virtual void render( double dt_sec ) = 0;

	virtual void update( double dt_sec ) = 0;

	virtual void on_event( const Event &event ) = 0;

protected:
	Engine *m_app;
	ResourceManager *m_res;
	WindowSystem *m_win;
};

} // namespace vv