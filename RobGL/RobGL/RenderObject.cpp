#include "RenderObject.h"
#include "MeshHelpers.h"
#include "Frustum.h"
namespace rgl {
	RenderObject::RenderObject()
	{
	}


	RenderObject::~RenderObject()
	{
	}

	void RenderObject::draw(float delta, GLuint program)
	{
		glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&_modelMatrix);

		if (_texture != nullptr) {
			_texture->bind();
		}


		_mesh->draw(delta, program);

		if (_texture != nullptr) {
			_texture->unbind();
		}
	}

	glm::vec3 RenderObject::getPosition()
	{
		return _modelMatrix[3];
	}

}