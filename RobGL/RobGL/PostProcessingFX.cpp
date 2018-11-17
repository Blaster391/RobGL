#include "PostProcessingFX.h"


namespace rgl {

	PostProcessingFX::PostProcessingFX(std::vector<Shader*> shaders, int iterations) 
		: ToScreenRenderPool(shaders, 0), _iterations(iterations)
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