#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

#include "glad/glad.h"
#include <External/glm/common.hpp>

namespace rgl {
	
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	class Text
	{
	public:
		Text(std::string font);
		~Text();
		Character getCharacter(char c);
	private:
		std::map<GLchar, Character> _characters;
	};


}
