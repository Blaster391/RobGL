#include "WaterUniform.h"

namespace rgl {

	WaterUniform::WaterUniform()
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
	}

}
