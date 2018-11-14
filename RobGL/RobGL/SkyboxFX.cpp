#include "SkyboxFX.h"

namespace rgl {


	SkyboxFX::SkyboxFX(std::vector<Shader*> shaders, Cubemap* skyboxTex, Texture* depthTex, Camera * perspective)
		: PostProcessingFX(shaders, 1), _perspective(perspective), _skyboxTex(skyboxTex), _depthTex(depthTex)
	{
	}

	SkyboxFX::~SkyboxFX()
	{
	}
	void SkyboxFX::process(float delta, GLuint & displayTex, GLuint & processTex)
	{
		if (!beginDraw()) {
			return;
		}

		glUniform1i(glGetUniformLocation(_program, "skybox"), 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTex->pointer());

		glUniform1i(glGetUniformLocation(_program, "depthTex"), 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _depthTex->pointer());

		glUniformMatrix4fv(glGetUniformLocation(_program, "inverseViewMatrix"), 1, false, (float*)&inverse(_perspective->getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(_program, "inverseProjectionMatrix"), 1, false, (float*)&inverse(_perspective->getProjectionMatrix()));

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, processTex, 0);

		_quadMesh->draw(delta, _program);

		GLuint temp = processTex;
		processTex = displayTex;
		displayTex = temp;

		glActiveTexture(GL_TEXTURE0);

		endDraw();
	}
}