#pragma once
#include "Vertex.h"
#include <vector>
#include "glad/glad.h"
namespace rgl {
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void setVerticies(std::vector<Vertex> verticies);
		void setIndicies(std::vector<unsigned int> indicies);

		void draw();

		void buffer();

	private:
		GLuint arrayObject;
		GLuint bufferObject;
		GLuint indexBuffer;

		GLuint	_meshType;

		std::vector<Vertex> _verticies;
		std::vector<unsigned int> _indicies;

		bool useIndicies;
	};

}

