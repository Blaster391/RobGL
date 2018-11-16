#include "DirectionalLightUniform.h"

namespace rgl {

	DirectionalLightUniform::DirectionalLightUniform(glm::vec4 colour, glm::vec3 position, glm::vec3 direction) : _colour(colour), _position(position), _direction(direction)
	{
	}

	DirectionalLightUniform::~DirectionalLightUniform()
	{
	}
	void DirectionalLightUniform::apply(GLuint program)
	{
		glUniform4f(glGetUniformLocation(program, "lightColour"), _colour.r, _colour.g, _colour.b, _colour.a);
		glUniform3f(glGetUniformLocation(program, "lightPosition"), _position.x, _position.y, _position.z);
		glUniform3f(glGetUniformLocation(program, "lightDirection"), _direction.x, _direction.y, _direction.z);
	}
}