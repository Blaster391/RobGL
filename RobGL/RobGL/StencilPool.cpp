#include "StencilPool.h"

namespace rgl {


	StencilPool::StencilPool(const std::vector<Shader*>& shaders, Camera * c) : RenderPool(shaders, c)
	{
	}

	StencilPool::~StencilPool()
	{
	}
	void StencilPool::draw()
	{
		if (!_enabled) {
			return;
		}

		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glStencilFunc(GL_ALWAYS, 2, ~0);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		

		RenderPool::draw();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 2, ~0);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	}
}
