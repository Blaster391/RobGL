#include "ParticleSystem.h"
#include <External/glm/glm.hpp>

namespace rgl {




	ParticleSystem::ParticleSystem(int numberOfParticles) : _numberOfParticles(numberOfParticles)
	{
		glGenBuffers(1, &_particleBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colour));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		auto flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfParticles, 0, flags);

		_vertexBufferData = (Vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * numberOfParticles, flags);

		for (int i = 0; i < _numberOfParticles; ++i) {
			_vertexBufferData[i] = Vertex();
			_vertexBufferData[i].Position = glm::vec3(0, i, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	ParticleSystem::~ParticleSystem()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffer);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_particleBuffer);
	}

	void ParticleSystem::draw(float delta)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffer);
		for (int i = 0; i < _numberOfParticles; ++i) {
			_vertexBufferData[i].Position = _vertexBufferData[i].Position + glm::vec3(0, 0, 0.01f);
		}

		glDrawArrays(GL_POINTS, 0, _numberOfParticles);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
