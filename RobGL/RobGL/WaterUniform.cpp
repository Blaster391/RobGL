#include "WaterUniform.h"

namespace rgl {


	WaterUniform::WaterUniform(Cubemap * reflection) : _reflection(reflection)
	{
	}

	WaterUniform::~WaterUniform()
	{
	}

	void rgl::WaterUniform::update(float delta)
	{
		_time += delta;
	}

	void rgl::WaterUniform::apply(GLuint program)
	{
		glUniform1f(glGetUniformLocation(program, "time"), _time);
		glUniform1f(glGetUniformLocation(program, "displacement"), _maxDisplacement);

		glUniform1i(glGetUniformLocation(program, "reflectionCube"), 15);
		glActiveTexture(GL_TEXTURE15);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _reflection->pointer());
		glActiveTexture(GL_TEXTURE0);
	}

}
