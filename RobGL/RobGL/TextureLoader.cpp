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

		stbi_image_free(image);


		return new Texture(tex, generateMips);
	}

	Cubemap* TextureLoader::LoadCubemapFromFile(std::vector<std::string> faces, bool generateMips)
	{
		int w;
		int h;
		int comp;

		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex);


		for (int i = 0; i < faces.size(); ++i) {
			unsigned char* image = stbi_load(faces[i].c_str(), &w, &h, &comp, STBI_default);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			stbi_image_free(image);
		}
		glTexParameterf(GL_TEXTURE_MAX_ANISOTROPY, GL_TEXTURE_CUBE_MAP, 16);

		glBindTexture(GL_TEXTURE_2D, 0);

		return new Cubemap(tex, generateMips);
	}
}