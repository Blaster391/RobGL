#include "Cubemap.h"

namespace rgl {

	Cubemap::Cubemap(GLuint texture, bool mipmapped) : Texture(texture, mipmapped)
	{
	}

	Cubemap::~Cubemap()
	{
	}

}

