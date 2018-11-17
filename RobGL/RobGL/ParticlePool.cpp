#include "ParticlePool.h"

namespace rgl {

	ParticlePool::ParticlePool(const std::vector<Shader*>& shaders, Camera * c, ParticleSystem * particles) : RenderPool(shaders, c), _particles(particles)
	{ 
	}

	ParticlePool::~ParticlePool()
	{
	}

	void ParticlePool::drawData(float delta)
	{
		_particles->draw(delta);
	}
}

