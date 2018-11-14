#include "SkyboxFX.h"

namespace rgl {


	SkyboxFX::SkyboxFX(std::vector<Shader*> shaders, Cubemap* skyboxTex, Camera * perspective) 
		: PostProcessingFX(shaders, 1), _perspective(perspective), _skyboxTex(skyboxTex)
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

		glBindTextureUnit(1, _skyboxTex->pointer());
		glUniform1i(glGetUniformLocation(_program, "skybox"), 1);

		glUniformMatrix4fv(glGetUniformLocation(_program, "inverseViewMatrix"), 1, false, (float*)&inverse(_perspective->getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(_program, "inverseProjectionMatrix"), 1, false, (float*)&inverse(_perspective->getProjectionMatrix()));

		_quadMesh->draw(delta, _program);

		glFlush();

		GLuint temp = processTex;
		processTex = displayTex;
		displayTex = processTex;

		endDraw();
	}
}