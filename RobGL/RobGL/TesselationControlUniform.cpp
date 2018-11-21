#include "TesselationControlUniform.h"

namespace rgl {


	TesselationControlUniform::TesselationControlUniform(const int outer[3], int inner) : _inner(inner)
	{
		_outer[0] = outer[0];
		_outer[1] = outer[1];
		_outer[2] = outer[2];

	}

	TesselationControlUniform::~TesselationControlUniform()
	{
	}

	void TesselationControlUniform::apply(GLuint program)
	{
		glUniform1i(glGetUniformLocation(program, "inner"), _inner);
		glUniform3i(glGetUniformLocation(program, "outer"), _outer[0], _outer[1], _outer[2]);
	}

}