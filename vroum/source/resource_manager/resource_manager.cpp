#include "resource_manager.hpp"
#include "core/logger.hpp"
#include "core/utilities.hpp"
#include "graphics/render_cmd.hpp"

namespace vv
{

Error ResourceManager::init( const std::string &root, RenderingSystem *render_sys )
{
    m_render_sys = render_sys;
    m_root = root;
    return Error::ok;
}

void ResourceManager::shutdown()
{
    for(auto &[_, val]: m_shaders)
    {
        if(val.is_null()) continue;
        m_render_sys->send_render_command( DestroyShaderCmd{val} );
    }
}

ShaderHandle ResourceManager::load_shader( const std::string &vs_path, const std::string &fs_path )
{
    std::string key = vs_path + "#" + fs_path;
    
    // Try to find an existing Shader
    auto it = m_shaders.find(key);
    if( it != m_shaders.end() )
    {
        return it->second;
    }

    // Load the files
    Opt<std::string> vs_source = load_file(m_root / vs_path);
    Opt<std::string> fs_source = load_file(m_root / fs_path);

    if( !vs_source.has_value() || !fs_source.has_value() )
    {
        VV_ERROR("Couls not read the shader source file");
        return ShaderHandle::null();
    }

    // Construct a RenderCmd to load the shader
    LoadShaderCmd cmd {
        .vs_source=vs_source.value(),
        .fs_source=fs_source.value()
    };
    auto future_shader = cmd.promise.get_future();

    // Send to the GPU and wait for the result
    m_render_sys->send_render_command( std::move(cmd) );

    // Return the handle
    Res<ShaderHandle> res = future_shader.get();

    if(!res.is_ok())
    {
        VV_ERROR("Could not create shader on the GPU side");
        return ShaderHandle::null();
    }

    m_shaders[key] = res.value();

    return res.value();
}

} // namespace vv