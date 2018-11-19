#include "AdditionalTextureUniform.h"

namespace rgl {

	AdditionalTextureUniform::AdditionalTextureUniform(Texture * texture, std::string textureName) : _textureName(textureName), _texture(texture), BaseUniform()
	{
	}

	AdditionalTextureUniform::~AdditionalTextureUniform()
	{
	}

	void AdditionalTextureUniform::apply(GLuint program)
	{
		glUniform1i(glGetUniformLocation(program, _textureName.c_str()), 10);
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, _texture->pointer());
		glActiveTexture(GL_TEXTURE0);
	}
}
