#pragma once
#include "RenderPool.h"
namespace rgl {
	class ShadowmapPool : public RenderPool
	{
	public:
		ShadowmapPool();
		~ShadowmapPool();

		virtual void drawData(float delta) override;
	};
}
