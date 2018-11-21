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
		glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, (float*)&_modelMatrix[3]);
		glUniform4fv(glGetUniformLocation(program, "lightColour"), 1, (float*)&_colour);

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
