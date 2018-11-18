#include "Text.h"
#include <iostream>


namespace rgl {

	Text::Text(std::string font)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout << "Freetype : Could not init FreeType Library" << std::endl;
		}
			
		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face)) {
			std::cout << "Freetype : failed to load font file" << std::endl;
		}
			
		FT_Set_Pixel_Sizes(face, 0, 96);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Freetype: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			_characters.insert(std::pair<GLchar, Character>(c, character));
		}
	}

	Character Text::getCharacter(char c)
	{
		return _characters[c];
	}

	Text::~Text()
	{
	}
}