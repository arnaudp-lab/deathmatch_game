#pragma once

#include "texture.hpp"
#include <string>

// TODO: change api to use Ref<Texture2D> load_from_file()

class Texture2D: public Texture
{
public:
	Texture2D():
		Texture()
	{
	}

	Texture2D( const std::string &path ):
		Texture()
	{
		load_from_file( path );
	}

	bool load_from_file( const std::string &path );

	void bind() const;
	void unbind() const;
};