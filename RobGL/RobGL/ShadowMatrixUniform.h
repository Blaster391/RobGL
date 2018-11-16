#pragma once
#include "BaseUniform.h"
namespace rgl {
	class ShadowMatrixUniform :
		public BaseUniform
	{
	public:
		ShadowMatrixUniform();
		virtual ~ShadowMatrixUniform();

		virtual void apply(GLuint program) override;
	};

}

