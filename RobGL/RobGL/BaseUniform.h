#pragma once
#include "glad/glad.h"
namespace rgl {
	class BaseUniform
	{
	public:
		BaseUniform();
		~BaseUniform();

		virtual void apply(GLuint program) = 0;
	};
}

