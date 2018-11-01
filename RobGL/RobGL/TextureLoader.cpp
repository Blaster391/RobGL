#define STB_IMAGE_IMPLEMENTATION

#include "TextureLoader.h"
#include <External/stb/stb_image.h>
#include "glad/glad.h"
#include "Texture.h"

#include <iostream>

namespace rgl {

	Texture * TextureLoader::LoadFromFile(std::string filename, bool hasAlpha, bool generateMips)
	{
		int w;
		int h;
		int comp;

		int loadType = STBI_rgb_alpha;
		if (!hasAlpha) {
			loadType = STBI_rgb;
		}

		unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, loadType);

		GLuint tex;
		glGenTextures(1, &tex);

		glBindTexture(GL_TEXTURE_2D, tex);

		if (comp == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if (comp == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}

		if (generateMips) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		//TODO set this somewhere else
		glTexParameterf(GL_TEXTURE_MAX_ANISOTROPY, GL_TEXTURE_2D, 16);

		glBindTexture(GL_TEXTURE_2D, 0);



		Texture* t = new Texture(tex, generateMips);

		return t;
	}
}