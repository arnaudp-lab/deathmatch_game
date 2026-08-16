#include "cubemap_texture.hpp"

#include "stb_image.h"
#include "core/logger.hpp"
#include "gldebug.hpp"

#include <glad/glad.h>

#include <cassert>
#include <stdexcept>

CubemapTexture::CubemapTexture( const std::initializer_list<std::string> &paths ):
	Texture()
{
	load_from_file( paths );
}

CubemapTexture::CubemapTexture(
	const std::string &right,
	const std::string &left,
	const std::string &top,
	const std::string &bottom,
	const std::string &front,
	const std::string &back ):
	CubemapTexture({right, left, top, bottom, front, back})
{
} 

bool CubemapTexture::load_from_file( const std::initializer_list<std::string> &paths )
{
	assert( paths.size() == 6 );

	m_valid = true;
	
	bind();

	stbi_set_flip_vertically_on_load(false);

	auto it = paths.begin();
	for( int i = 0; i < paths.size() ; ++i ) {
		int32_t w, h, nb_channels;

		// TODO: régler le problème de chemin
		uint8_t *data = stbi_load( (std::string{"../"} + *it).c_str(), &w, &h, &nb_channels, 0);
		if( data ) {
			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		}
		else {
			m_valid = false;
			VV_ERROR( "Impossible d'ouvrir ", *it );
		}

		stbi_image_free(data);
		++it;
	}

	stbi_set_flip_vertically_on_load(true);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	unbind();

	log_gl_errors();

	return m_valid;
}

bool CubemapTexture::load_from_file( const std::string &right,
	const std::string &left,
	const std::string &top,
	const std::string &bottom,
	const std::string &front,
	const std::string &back )
{
	return load_from_file( {right, left, top, bottom, front, back} );
}

void CubemapTexture::bind() const
{
	assert(m_valid);
	glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );
}

void CubemapTexture::unbind() const
{
	assert(m_valid);
	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
}