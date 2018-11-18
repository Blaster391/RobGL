#pragma once
#include "glad/glad.h"
#include "Vertex.h"
#include <External/glm/mat4x4.hpp>
#include "Texture.h"

namespace rgl {
	class ParticleSystem
	{
	public:
		ParticleSystem(int numberOfParticles);
		~ParticleSystem();

		virtual void draw(float delta);

		float getParticleSize();
		void setParticleSize(float size);

		void setModelMatrix(glm::mat4x4 modelMatrix);
		glm::mat4 getModelMatrix();

		Vertex* getParticleBuffer();

		Texture* getTexture();
		void setTexture(Texture* tex);

	private:
		GLuint _arrayObject;
		GLuint _particleBuffer;
		Vertex* _vertexBufferData;
		int _numberOfParticles;

		float _particleSize = 0.1f;

		Texture* _texture = nullptr;

		glm::mat4x4 _modelMatrix;
	};
}


