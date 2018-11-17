#pragma once
#include "glad/glad.h"
#include "Vertex.h"

namespace rgl {
	class ParticleSystem
	{
	public:
		ParticleSystem(int numberOfParticles);
		~ParticleSystem();

		virtual void draw(float delta);

	private:
		GLuint _particleBuffer;
		Vertex* _vertexBufferData;
		int _numberOfParticles;
	};
}


