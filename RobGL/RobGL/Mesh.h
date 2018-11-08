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

		std::vector<Vertex>& getVertices() {
			return _verticies;
		}

		void setVerticies(std::vector<Vertex> verticies);
		void setIndicies(std::vector<unsigned int> indicies);

		virtual void draw(GLuint program);

		virtual void buffer();

		void rebuffer();

		virtual void clear();
	protected:
		void beginBuffer();
		void basicBuffer();
		void endBuffer();

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

