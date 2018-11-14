#pragma once
#include "Texture.h"
namespace rgl { 
	class Cubemap : public Texture
	{
	public:
		Cubemap(GLuint texture, bool mipmapped);
		virtual ~Cubemap();
	};

}

