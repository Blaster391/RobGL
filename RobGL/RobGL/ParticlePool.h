#pragma once
#include "RenderPool.h"
#include "ParticleSystem.h"
namespace rgl {
	class ParticlePool :
		public RenderPool
	{
	public:
		ParticlePool(const std::vector<Shader*>& shaders, Camera* c, ParticleSystem* particles);
		virtual ~ParticlePool();

	protected:
		virtual void drawData(float delta) override;
		ParticleSystem* _particles;
	};

}

