#include "Mesh.h"


namespace rgl {
	Mesh::Mesh()
	{
		glGenVertexArrays(1, &arrayObject);
		_meshType = GL_TRIANGLES;

	}
	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &arrayObject);
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
		glBindVertexArray(arrayObject);
		if (useIndicies) {
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
	void Mesh::rebuffer()
	{
		clear();
		buffer();
	}
	void Mesh::clear()
	{
		glDeleteBuffers(1, &bufferObject);
		if (useIndicies) {
			glDeleteBuffers(1, &indexBuffer);
		}
	}
	void Mesh::beginBuffer()
	{
		glBindVertexArray(arrayObject);
	}
	void Mesh::basicBuffer()
	{
		useIndicies = (_indicies.size() > 0);
		glGenBuffers(1, &bufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
		glBufferData(GL_ARRAY_BUFFER, _verticies.size() * sizeof(Vertex), _verticies.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colour));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		if (useIndicies) {
			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicies.size() * sizeof(GLuint), _indicies.data(), GL_STATIC_DRAW);
		}
	}
	void Mesh::endBuffer()
	{
		glBindVertexArray(0);
	}
}