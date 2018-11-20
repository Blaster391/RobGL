#include "LerpSkyboxUniform.h"




LerpSkyboxUniform::LerpSkyboxUniform(rgl::Cubemap * secondSkybox, rgl::Cubemap * thirdSkybox, float tweenTime) : _secondSkybox(secondSkybox), _thirdSkybox(thirdSkybox), _tweenTime(tweenTime)
{
}

LerpSkyboxUniform::~LerpSkyboxUniform()
{
}

void LerpSkyboxUniform::update(float delta)
{
	_currentTime += delta;
	if (_tweenTime < _currentTime) {
		_currentTime -= _tweenTime;
	}

}

void LerpSkyboxUniform::apply(GLuint program)
{
	glUniform1i(glGetUniformLocation(program, "skybox2"), 11);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _secondSkybox->pointer());
	glUniform1i(glGetUniformLocation(program, "skybox3"), 12);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _thirdSkybox->pointer());

	glUniform1f(glGetUniformLocation(program, "tweenTime"), _tweenTime);
	glUniform1f(glGetUniformLocation(program, "currentTime"), _currentTime);
}
