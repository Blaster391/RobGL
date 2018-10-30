#pragma once
#include "Mesh.h"
#include <External/glm/mat4x4.hpp>
namespace rgl {

	class RenderObject
	{
	public:
		RenderObject();
		~RenderObject();

		void draw(GLuint program);
	private:
		Mesh* _mesh;
		glm::mat4x4 _modelMatrix;
	};

}

