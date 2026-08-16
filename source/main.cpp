#include "vv.hpp"
#include "main_menu.hpp"
#include <memory>

vv::EngineParameters load_params()
{
	vv::EngineParameters params;

	params.window_height = 1080;
	params.window_width = 1920;
	params.window_title = "ECO+ Deathmatch";
	params.resources_root = "../resources";

	return params;
}

int main()
{
	auto params = load_params();

	vv::run_application(params, std::make_unique<MainMenu>());
	
	return 0;
}