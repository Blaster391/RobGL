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
		_baseSkeleton = sk;
	}

	void AnimatedMesh::setAnimations(std::vector<Animation> animations)
	{
		_animations = animations;
	}

	void AnimatedMesh::draw(float delta, GLuint program)
	{

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

	Skeleton* AnimatedMesh::generateSkeleton()
	{
		Joint* baseRoot = _baseSkeleton->getRoot();
		auto baseJoints = _baseSkeleton->getJoints();

		Joint* root = new Joint(*baseRoot);
		std::vector<Joint*> joints;
		for (auto& j : baseJoints) {
			joints.push_back(new Joint(*j.second));
		}

		Skeleton* sk = new Skeleton;
		sk->setJoints(root, joints);
		return sk;
	}
	Animation AnimatedMesh::getAnimation(int animation)
	{
		return _animations[animation];
	}
}