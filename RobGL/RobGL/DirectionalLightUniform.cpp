#include "DirectionalLightUniform.h"

namespace rgl {

	DirectionalLightUniform::DirectionalLightUniform(glm::vec4 colour, glm::vec3 position, glm::mat4 rotationMatrix) : _colour(colour), _position(position), _rotation(rotationMatrix)
	{
	}

	DirectionalLightUniform::~DirectionalLightUniform()
	{
	}
	void DirectionalLightUniform::apply(GLuint program)
	{
		glUniform4f(glGetUniformLocation(program, "lightColour"), _colour.r, _colour.g, _colour.b, _colour.a);
		glUniform3f(glGetUniformLocation(program, "lightPosition"), _position.x, _position.y, _position.z);
		glUniformMatrix4fv(glGetUniformLocation(program, "lightRotation"), 1, false, (float*)&_rotation);
	}
}