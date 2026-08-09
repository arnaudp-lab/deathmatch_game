#include "main_menu.hpp"
#include <cmath>
#include "core/logger.hpp"

MainMenu::~MainMenu()
{

}

vv::Error MainMenu::init() 
{
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
    using namespace vv;

    std::visit( [](auto &&e)
    {
        using T = std::decay_t<decltype(e)>;

        if constexpr( std::is_same_v<T, MouseMoveEvent> )
            VV_INFO("mouse_move x=", e.x, " y=", e.y, " dx=", e.dx, " dy=", e.dy);

        else if constexpr( std::is_same_v<T, MouseScrollEvent> )
            VV_INFO("mouse_scroll dx=", e.dx, " dy=", e.dy);

        else if constexpr( std::is_same_v<T, MouseClickEvent> )
            VV_INFO("mouse_click button=", (int)e.button, " pressed=", e.pressed,
                   " x=", e.x, " y=", e.y);

        else if constexpr( std::is_same_v<T, KeydownEvent> )
            VV_INFO("key_down key=", (int)e.key, " repeat=", e.repeat);

        else if constexpr( std::is_same_v<T, KeyupEvent> )
            VV_INFO("key_up key=", (int)e.key);

        else if constexpr( std::is_same_v<T, WindowResizeEvent> )
            VV_INFO("window_resize width=", e.width, " height=", e.height);

    }, event.data );
}