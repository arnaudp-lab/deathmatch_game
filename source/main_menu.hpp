#include "graphics/gpu_device.hpp"
#include "vv.hpp"

class MainMenu: public vv::Layer
{
public:
	~MainMenu() override;

	vv::Error init() override;

	void shutdown() override;

	void update( double dt_sec ) override;

	void render( double dt_sec ) override;

	void on_event( const vv::Event &event ) override;

private:
	float m_time;
	vv::ShaderHandle test_handle;
};