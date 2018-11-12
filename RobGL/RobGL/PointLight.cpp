#include "PointLight.h"


namespace rgl {
	PointLight::PointLight(glm::vec4 colour) : RenderObject(), _colour(colour)
	{
		
	}

	PointLight::~PointLight()
	{
	}
	void PointLight::draw(float delta, GLuint program)
	{
		glUniform1f(glGetUniformLocation(program, "lightRadius"), _modelMatrix[0].x);
		glUniform3f(glGetUniformLocation(program, "lightPos"), _modelMatrix[3].x, _modelMatrix[3].y, _modelMatrix[3].z);
		glUniform4f(glGetUniformLocation(program, "lightColour"), _colour.x, _colour.y, _colour.z, _colour.w);

		RenderObject::draw(delta, program);
	}
	void PointLight::setColour(glm::vec4 colour)
	{
		_colour = colour;
	}

	glm::vec4 PointLight::getColour()
	{
		return _colour;
	}
}
