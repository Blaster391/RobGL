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
		glClear(GL_DEPTH_BUFFER_BIT);

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		RenderPool::drawData(delta);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}
}
