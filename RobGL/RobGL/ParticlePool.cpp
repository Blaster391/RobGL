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
		glUniformMatrix4fv(glGetUniformLocation(_program, "modelMatrix"), 1, false, (float*)&_particles->getModelMatrix());
		glUniform1f(glGetUniformLocation(_program, "particleSize"), _particles->getParticleSize());
		_particles->draw(delta);
	}
}

