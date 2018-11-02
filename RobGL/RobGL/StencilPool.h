#pragma once
#include "RenderPool.h"

namespace rgl {
	class StencilPool : public RenderPool
	{
	public:
		StencilPool(const std::vector<Shader*>& shaders, Camera* c);
		~StencilPool();

		virtual void draw();
	};
}


