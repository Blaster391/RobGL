#include "ScreenInformationUniform.h"

namespace rgl {

	ScreenInformationUniform::ScreenInformationUniform(int width, int height) : BaseUniform(), _width(width), _height(height)
	{
	}

	ScreenInformationUniform::~ScreenInformationUniform()
	{
	}
	void ScreenInformationUniform::apply(GLuint program)
	{
		glUniform2f(glGetUniformLocation(program, "pixelSize"), 1.0f / _width, 1.0f / _height);

		glUniform1f(glGetUniformLocation(program, "width"), _width);
		glUniform1f(glGetUniformLocation(program, "height"), _height);

	}
	void ScreenInformationUniform::updateScreenSize(int width, int height)
	{
		_width = width;
		_height = height;
	}
}