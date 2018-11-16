#pragma once
#include "RenderPool.h"
namespace rgl {
	class ShadowmapPool : public RenderPool
	{
	public:
		ShadowmapPool(const std::vector<Shader*>& shaders, Camera* c);
		~ShadowmapPool();

		virtual void drawData(float delta) override;
	};
}
