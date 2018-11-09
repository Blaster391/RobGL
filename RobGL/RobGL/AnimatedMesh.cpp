#include "AnimatedMesh.h"

#include <iostream>

namespace rgl {
	AnimatedMesh::AnimatedMesh()
	{
	}


	AnimatedMesh::~AnimatedMesh()
	{
	}

	void AnimatedMesh::setVerticiesWeightData(std::vector<VertexWeightData> data)
	{
		_verticiesWeightData = data;
	}
	std::vector<VertexWeightData> AnimatedMesh::getVerticiesWeightData()
	{
		return _verticiesWeightData;
	}
	void AnimatedMesh::setSkeleton(Skeleton* sk)
	{
		_skeleton = sk;
	}

	void AnimatedMesh::setAnimations(std::vector<Animation> animations)
	{
		_animations = animations;
	}

	void AnimatedMesh::draw(float delta, GLuint program)
	{
		if (_activeAnimation != nullptr) {
			_activeAnimation->update(delta);
		}
		auto debug = _skeleton->getJointMatrices();
		glUniformMatrix4fv(glGetUniformLocation(program, "jointMatrices"), 50, false, (float*)_skeleton->getJointMatrices());
		Mesh::draw(delta,program);
	}

	void AnimatedMesh::buffer()
	{
		beginBuffer();
		basicBuffer();

		glGenBuffers(1, &weightBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, weightBuffer);
		glBufferData(GL_ARRAY_BUFFER, _verticiesWeightData.size() * sizeof(VertexWeightData), _verticiesWeightData.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexWeightData), (void*)offsetof(VertexWeightData, Joints));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexWeightData), (void*)offsetof(VertexWeightData, Weights));
	    glEnableVertexAttribArray(5);

		endBuffer();
	}
	void AnimatedMesh::setGlobalTransform(glm::mat4 transform)
	{
		_skeleton->setGlobalTransform(transform);
	}
	void AnimatedMesh::setActiveAnimation(int anim)
	{
		_activeAnimation = &_animations[anim];
	}
}