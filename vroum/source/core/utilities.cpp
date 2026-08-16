#include "utilities.hpp"
#include <fstream>
#include <iterator>

namespace vv
{
    
std::string trim( const std::string &str )
{
    auto first = str.find_first_not_of(' ');
    auto last = str.find_last_not_of(' ');
    return str.substr(first, last+1);
}

Opt<std::string> load_file( const std::filesystem::path &path )
{
    std::fstream file{ path };

	if(!file)
	{
		VV_WARN("cannot get the content of: ", path, "\n");
		return {};
	}

	file << std::noskipws;
	std::string source { std::istream_iterator<char>(file), std::istream_iterator<char>() };
    file.close();
    
    return source;
}

float map( float v, float min1, float max1, float min2, float max2)
{
	return min2 + ((v - min1) / (max1 - min1)) * (max2-min2);
}

float to_01( float v, float m, float M )
{
	return (v - m) / (M - m);
}

} // namespace vv