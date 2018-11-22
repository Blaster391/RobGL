#include "ShadowmapPool.h"

namespace rgl {

	ShadowmapPool::ShadowmapPool(const std::vector<Shader*>& shaders, Camera * c) : RenderPool(shaders, c)
	{
	}

	ShadowmapPool::~ShadowmapPool()
	{
	}
	void ShadowmapPool::drawData(float delta)
	{
		//glCullFace(GL_FRONT);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		RenderPool::drawData(delta);
		//glCullFace(GL_BACK);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}
}
