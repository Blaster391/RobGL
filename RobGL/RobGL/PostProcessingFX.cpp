#include "PostProcessingFX.h"


namespace rgl {

	PostProcessingFX::PostProcessingFX(std::vector<Shader*> shaders, int iterations) : ToScreenRenderPool(shaders, 0), _iterations(iterations)
	{
	}

	PostProcessingFX::~PostProcessingFX()
	{
	}
	void PostProcessingFX::process(float delta, int width, int height, GLuint flipTex, GLuint flopTex)
	{
		//TODO set uniforms
		glUniform2f(glGetUniformLocation(_program, "pixelSize"), 1.0f / 800, 1.0f / 600);

		for (int i = 0; i < _iterations; ++i) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, flopTex, 0);
			_quadTexture->setPointer(flipTex);
			draw(delta);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, flipTex, 0);
			_quadTexture->setPointer(flopTex);
			draw(delta);
		}
	}

}