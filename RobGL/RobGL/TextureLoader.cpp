#define STB_IMAGE_IMPLEMENTATION

#include "TextureLoader.h"
#include <External/stb/stb_image.h>
#include "glad/glad.h"
#include "Texture.h"

#include <iostream>

namespace rgl {
	Texture* TextureLoader::LoadFromPNG(std::string filename, bool generateMips)
	{
		int w;
		int h;
		int comp;
		unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb);

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

		glBindTexture(GL_TEXTURE_2D, 0);



		Texture* t = new Texture(tex, generateMips);

		return t;
	}
}