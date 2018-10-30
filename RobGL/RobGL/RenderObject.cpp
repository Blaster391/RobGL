#include "RenderObject.h"
#include "MeshHelpers.h"
namespace rgl {
	RenderObject::RenderObject()
	{
		//TODO lol not this
		_mesh = MeshHelpers::GenerateTriangle();
	}


	RenderObject::~RenderObject()
	{
	}

	void RenderObject::draw(GLuint program)
	{
		//
		glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&_modelMatrix);

		_mesh->draw();
	}
}