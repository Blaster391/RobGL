#include "ParticleSystem.h"
#include <External/glm/glm.hpp>

namespace rgl {




	ParticleSystem::ParticleSystem(int numberOfParticles) : _numberOfParticles(numberOfParticles)
	{
		glGenVertexArrays(1, &_arrayObject);
		glBindVertexArray(_arrayObject);

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

		auto flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;


		glBufferStorage(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfParticles, nullptr, flags);

		_vertexBufferData = (Vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * numberOfParticles, flags);

		for (int i = 0; i < _numberOfParticles; ++i) {
			_vertexBufferData[i] = Vertex();
			_vertexBufferData[i].Position = glm::vec3(10, i * 0.01f, 0);
			_vertexBufferData[i].Colour = glm::vec4(1, 1, 1, 1);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	ParticleSystem::~ParticleSystem()
	{

		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffer);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_particleBuffer);
		glDeleteVertexArrays(1, &_arrayObject);

	}

	float colour = 0;

	void ParticleSystem::draw(float delta)
	{
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(_arrayObject);

		colour = colour + delta;
		if (colour > 1) {
			colour = 0;
		}
		for (int i = 0; i < _numberOfParticles; ++i) {
			_vertexBufferData[i].Position = glm::vec3(sin(colour * i), i * colour, 0);
			_vertexBufferData[i].Colour = glm::vec4(colour, 0, 1, 1);


		}

		if (_texture != nullptr) {
			_texture->bind();
		}

		glDrawArrays(GL_POINTS, 0, _numberOfParticles);

		if (_texture != nullptr) {
			_texture->unbind();
		}
		glBindVertexArray(0);
		glEnable(GL_DEPTH_TEST);
	}
	float ParticleSystem::getParticleSize()
	{
		return _particleSize;
	}
	void ParticleSystem::setParticleSize(float size)
	{
		_particleSize = size;
	}
	void ParticleSystem::setModelMatrix(glm::mat4x4 modelMatrix)
	{
		_modelMatrix = modelMatrix;
	}
	glm::mat4 ParticleSystem::getModelMatrix()
	{
		return _modelMatrix;
	}
	Vertex * ParticleSystem::getParticleBuffer()
	{
		return _vertexBufferData;
	}
	Texture * ParticleSystem::getTexture()
	{
		return _texture;
	}
	void ParticleSystem::setTexture(Texture * tex)
	{
		_texture = tex;
	}
}
