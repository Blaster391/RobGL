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
		//TODO get is bad?
		glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&_modelMatrix);

		//TODO failover tex?
		if (_texture != nullptr) {
			_texture->bind();
			//glUniform1i(glGetUniformLocation(program, "tex"), _texture->pointer());
		}


		_mesh->draw();

		if (_texture != nullptr) {
			_texture->unbind();
			//glUniform1i(glGetUniformLocation(program, "tex"), _texture->pointer());
		}
	}
}