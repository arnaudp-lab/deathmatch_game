#include "run_application.hpp"
#include "core/logger.hpp"
#include "engine.hpp"

void vv::run_application( const vv::EngineParameters &params,  vv::Box<vv::Layer> &&initial_layer)
{	
	vv::Engine application (params);

	vv::Error err = vv::Error::ok;
	
	err = application.init_systems();

	err = application.add_layer( std::move(initial_layer) );

    if(err == vv::Error::ok)
    {
	    application.run();
    }
    else
    {
        VV_ERROR("Could not initialize the game layer");
    }

	application.shutdown_systems();
}