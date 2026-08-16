#pragma once

#include "graphics/rendering_system.hpp"
#include <filesystem>
#include <map>

namespace vv
{

class ResourceManager
{
public:
    ResourceManager() {}
    ~ResourceManager() {}

    Error init( const std::string &root, RenderingSystem *render_sys );
    void shutdown();

    ShaderHandle load_shader( const std::string &vs_path, const std::string &fs_path );

private:
    std::filesystem::path m_root;
    RenderingSystem *m_render_sys;

    std::map<std::string, ShaderHandle> m_shaders;
};

} // namespace vv