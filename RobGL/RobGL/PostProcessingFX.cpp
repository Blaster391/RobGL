#include "PostProcessingFX.h"


namespace rgl {

	PostProcessingFX::PostProcessingFX(std::vector<Shader*> shaders, int iterations) : ToScreenRenderPool(shaders, 0), _iterations(iterations)
	{
	}

	PostProcessingFX::~PostProcessingFX()
	{
	}
	void PostProcessingFX::process(float delta, GLuint& displayTex, GLuint& processTex)
	{
		if (!beginDraw()) {
			return;
		}


		//TODO set uniforms
		glUniform2f(glGetUniformLocation(_program, "pixelSize"), 1.0f / 800, 1.0f / 600);

		glUniform1f(glGetUniformLocation(_program, "width"), 800);
		glUniform1f(glGetUniformLocation(_program, "height"), 600);

		for (int i = 0; i < _iterations; ++i) {
			
			glUniform1i(glGetUniformLocation(_program, "iteration"), i);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, processTex, 0);
			_quadTexture->setPointer(displayTex);
			_quadObject->draw(delta, _program);

			GLuint temp = processTex;
			processTex = displayTex;
			displayTex = temp;
		}


		endDraw();
	}

}