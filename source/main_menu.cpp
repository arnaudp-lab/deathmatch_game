#include "main_menu.hpp"
#include <cmath>
#include "core/logger.hpp"

MainMenu::~MainMenu()
{

}

vv::Error MainMenu::init() 
{
    test_handle = m_res->load_shader("shaders/mesh.vert.glsl", "shaders/mesh.frag.glsl");

    if( test_handle.is_null() )
    {
        VV_ERROR("Could not load the shader :(");
    }
    else
    {
        VV_INFO("The shader was loaded !");
    }

	return vv::Error::ok;
}

void MainMenu::shutdown() 
{

}

void MainMenu::update( double dt_sec )
{
	m_time += dt_sec;
}

void MainMenu::render( double dt_sec )
{
}
void MainMenu::on_event( const vv::Event &event )
{
}