#include "StencilPool.h"

namespace rgl {


	StencilPool::StencilPool(const std::vector<Shader*>& shaders, Camera * c) : RenderPool(shaders, c)
	{
	}

	StencilPool::~StencilPool()
	{
	}
	void StencilPool::drawData(float delta)
	{
		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glStencilFunc(GL_ALWAYS, 2, ~0);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		

		RenderPool::drawData(delta);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 2, ~0);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	}
}
