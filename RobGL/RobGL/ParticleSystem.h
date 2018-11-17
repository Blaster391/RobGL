#pragma once
#include "glad/glad.h"
#include "Vertex.h"
#include <External/glm/mat4x4.hpp>

namespace rgl {
	class ParticleSystem
	{
	public:
		ParticleSystem(int numberOfParticles);
		~ParticleSystem();

		virtual void draw(float delta);

		void setModelMatrix(glm::mat4x4 modelMatrix);
		glm::mat4 getModelMatrix();
	private:
		GLuint _arrayObject;
		GLuint _particleBuffer;
		Vertex* _vertexBufferData;
		int _numberOfParticles;

		glm::mat4x4 _modelMatrix;
	};
}


