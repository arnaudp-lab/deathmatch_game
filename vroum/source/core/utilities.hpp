#pragma once

#include "vv_headers.hpp"
#include <string>
#include <filesystem>

namespace vv
{

Opt<std::string> load_file(const std::filesystem::path &file_path);

std::string trim( const std::string &str );

float map( float v, float min1, float max1, float min2, float max2);

float to_01( float v, float m, float M );

} // namespace vv