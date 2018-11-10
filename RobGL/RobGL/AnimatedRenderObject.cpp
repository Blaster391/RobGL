#include "AnimatedRenderObject.h"

namespace rgl {
	AnimatedRenderObject::AnimatedRenderObject()
	{
	}


	AnimatedRenderObject::~AnimatedRenderObject()
	{
	}
	void AnimatedRenderObject::draw(float delta, GLuint program)
	{
		_mesh->setGlobalTransform(_modelMatrix);
		RenderObject::draw(delta, program);
	}
}


