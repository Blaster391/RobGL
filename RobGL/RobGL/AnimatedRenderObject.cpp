#include "AnimatedRenderObject.h"

namespace rgl {
	AnimatedRenderObject::AnimatedRenderObject()
	{
	}


	AnimatedRenderObject::~AnimatedRenderObject()
	{
	}
	void AnimatedRenderObject::update(float delta)
	{
		_activeAnimation.update(delta);
		_skeleton->updateJointMatrices();
	}

	void AnimatedRenderObject::draw(float delta, GLuint program)
	{
		setGlobalTransform(_modelMatrix);



		glUniformMatrix4fv(glGetUniformLocation(program, "jointMatrices"), 50, false, (float*)_skeleton->getJointMatrices());

		RenderObject::draw(delta, program);
	}
	void AnimatedRenderObject::setGlobalTransform(glm::mat4 transform)
	{
		_skeleton->setGlobalTransform(transform);
	}

	void AnimatedRenderObject::setActiveAnimation(int anim,float offset)
	{
		//Copy the animation from the mesh and rewrite the joints
		_activeAnimation = _mesh->getAnimation(anim);
	
		for (auto& ch : _activeAnimation.getChannels()) {
			auto baseJoint = ch.getTargetJoint();
			ch.setTargetJoint(_skeleton->getJoint(baseJoint->getIndex()));
		}

		//Set to time offset
		_activeAnimation.update(offset);
	}

}


