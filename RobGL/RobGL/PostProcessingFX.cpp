#include "PostProcessingFX.h"


namespace rgl {

	PostProcessingFX::PostProcessingFX(std::vector<Shader*> shaders, int iterations) : ToScreenRenderPool(shaders, 0), _iterations(iterations)
	{
	}

	PostProcessingFX::~PostProcessingFX()
	{
	}
	void PostProcessingFX::process(float delta, GLuint flipTex, GLuint flopTex)
	{
		if (!beginDraw()) {
			return;
		}


		//TODO set uniforms
		//glUniform2f(glGetUniformLocation(_program, "pixelSize"), 1.0f / 800, 1.0f / 600);

		for (int i = 0; i < _iterations; ++i) {
			
			glUniform1i(glGetUniformLocation(_program, "iteration"), i * 2 + 1);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, flopTex, 0);
			_quadTexture->setPointer(flipTex);
			_quadObject->draw(delta, _program);


			glUniform1i(glGetUniformLocation(_program, "iteration"), i*2);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, flipTex, 0);
			_quadTexture->setPointer(flipTex);
			_quadObject->draw(delta, _program);


		}


		endDraw();
	}

}