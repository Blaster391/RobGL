#include "DirectionalLightUniform.h"
#include "Camera.h"

#include <iostream>

namespace rgl {

	DirectionalLightUniform::DirectionalLightUniform(glm::vec4 colour, glm::vec3 direction, Camera* shadowPositionCamera) 
		: _colour(colour), _direction(direction), _shadowCamera(shadowPositionCamera)
	{
	}

	DirectionalLightUniform::~DirectionalLightUniform()
	{
	}
	void DirectionalLightUniform::apply(GLuint program)
	{

		auto position = _shadowCamera->getPosition();

		glm::vec3 direction = _shadowCamera->getDirection();

		glUniform4fv(glGetUniformLocation(program, "lightColour"),1, (float*)&_colour);
		glUniform3fv(glGetUniformLocation(program, "lightPosition"),1, (float*)&position);
		glUniform3fv(glGetUniformLocation(program, "lightDirection"),1, (float*)&_direction);

		auto shadowMatrix = _shadowCamera->getProjectionMatrix() * _shadowCamera->getViewMatrix();

		glUniformMatrix4fv(glGetUniformLocation(program, "shadowMatrix"), 1, false, (float*)&(shadowMatrix));

		//Enable shadows in shader
		glUniform1i(glGetUniformLocation(program, "useShadows"), 1);

		glUniform1i(glGetUniformLocation(program, "shadowTex"), 5);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, _shadowTex);
		glActiveTexture(GL_TEXTURE0);
	}
}