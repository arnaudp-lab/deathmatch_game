#include "core/errors.hpp"
#include "vv.hpp"
#include "main_menu.hpp"

vv::EngineParameters load_params()
{
	vv::EngineParameters params;

	params.window_height = 1080;
	params.window_width = 1920;
	params.window_title = "ECO+ Deathmatch";

	return params;
}

int main() {
	
	auto params = load_params();

	vv::Engine application (params);

	vv::Error err = vv::Error::ok;
	
	err = application.init_systems();

	VV_ERROR("Any Error ?: ", vv::get_err_msg(err) );

	err = application.add_layer<MainMenu>();

	VV_ERROR("Any Error ?: ", vv::get_err_msg(err) );

	application.run();

	application.shutdown_systems();
	
	return 0;
}