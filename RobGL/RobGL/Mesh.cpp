#include "Mesh.h"

#include <External/glm/gtc/matrix_transform.hpp>

namespace rgl {
	Mesh::Mesh()
	{
		glGenVertexArrays(1, &_arrayObject);
		_meshType = GL_TRIANGLES;

	}
	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &_arrayObject);
		clear();
	}

	void Mesh::setVerticies(std::vector<Vertex> verticies)
	{
		_verticies = verticies;
	}
	void Mesh::setIndicies(std::vector<unsigned int> indicies)
	{
		_indicies = indicies;
	}
	void Mesh::draw(float delta, GLuint program)
	{		
		glBindVertexArray(_arrayObject);
		if (_useIndicies) {
			glDrawElements(_meshType, _indicies.size(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(_meshType, 0, _verticies.size());
		}

		glBindVertexArray(0);
	}
	void Mesh::buffer()
	{
		beginBuffer();
		basicBuffer();
		endBuffer();


	}

	void Mesh::setHasPregeneratedNormals(bool val)
	{
		_hasPregeneratedNormals = val;
	}

	void Mesh::generateNormals()
	{
		if (_useIndicies) {
			for (int i = 0; i < _indicies.size(); i += 3) {
				unsigned int a = _indicies[i];
				unsigned int b = _indicies[i + 1];
				unsigned int c = _indicies[i + 2];

				glm::vec3 normal = glm::cross(_verticies[b].Position - _verticies[a].Position, _verticies[c].Position - _verticies[a].Position);

				_verticies[a].Normal += normal;
				_verticies[b].Normal += normal;
				_verticies[c].Normal += normal;
			}

		}
		else {
			for (int i = 0; i < _verticies.size(); i += 3) {
				glm::vec3 a = _verticies[i].Position;
				glm::vec3 b = _verticies[i+1].Position;
				glm::vec3 c = _verticies[i+2].Position;

				glm::vec3 normal = glm::cross(b - a, c - a);

				_verticies[i].Normal = normal;
				_verticies[i+1].Normal = normal;
				_verticies[i+2].Normal = normal;
			}
		}

		for (int i = 0; i < _verticies.size(); ++i) {
			_verticies[i].Normal = glm::normalize(_verticies[i].Normal);
		}
	}

	void Mesh::rebuffer()
	{
		clear();
		buffer();
	}
	void Mesh::clear()
	{
		glDeleteBuffers(1, &_bufferObject);
		if (_useIndicies) {
			glDeleteBuffers(1, &_indexBuffer);
		}
	}
	void Mesh::beginBuffer()
	{
		glBindVertexArray(_arrayObject);
	}
	void Mesh::basicBuffer()
	{
		_useIndicies = (_indicies.size() > 0);

		if (!_hasPregeneratedNormals) {
			generateNormals();
		}

		glGenBuffers(1, &_bufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, _bufferObject);
		glBufferData(GL_ARRAY_BUFFER, _verticies.size() * sizeof(Vertex), _verticies.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colour));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		if (_useIndicies) {
			glGenBuffers(1, &_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicies.size() * sizeof(GLuint), _indicies.data(), GL_STATIC_DRAW);
		}
	}
	void Mesh::endBuffer()
	{
		glBindVertexArray(0);
	}
}