#include "Texture.h"


namespace rgl {
	Texture::Texture(GLuint texture, bool mipmapped) :  _pointer(texture), _mipmapped(mipmapped)
	{
		setFiltering(true);
	}


	Texture::~Texture()
	{
	}
	void Texture::setFiltering(bool enable)
	{
		bind();
		if (enable) {
			if (_mipmapped) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		unbind();
	}
}