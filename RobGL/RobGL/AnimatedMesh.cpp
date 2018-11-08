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

	void AnimatedMesh::draw(GLuint program)
	{
		glUniformMatrix4fv(glGetUniformLocation(program, "jointMatrices"), 50, false, (float*)_skeleton->getJointMatrices());
		Mesh::draw(program);
	}

	void AnimatedMesh::buffer()
	{
		beginBuffer();
		basicBuffer();

		glGenBuffers(1, &weightBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, weightBuffer);
		glBufferData(GL_ARRAY_BUFFER, _verticiesWeightData.size() * sizeof(VertexWeightData), _verticiesWeightData.data(), GL_STATIC_DRAW);
		//for (auto& vwd : _verticiesWeightData) {
		//	std::cout << vwd.Joints.x << "," << vwd.Joints.y << "," << vwd.Joints.z << "," << vwd.Joints.w << std::endl;
		//	std::cout << vwd.Weights.x << "," << vwd.Weights.y << "," << vwd.Weights.z << "," << vwd.Weights.w << std::endl;
		//}

		glVertexAttribPointer(4, 4, GL_UNSIGNED_SHORT, GL_FALSE, sizeof(VertexWeightData), (void*)offsetof(VertexWeightData, Joints));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexWeightData), (void*)offsetof(VertexWeightData, Weights));
	    glEnableVertexAttribArray(5);

		endBuffer();
	}
	void AnimatedMesh::setGlobalTransform(glm::mat4 transform)
	{
		_skeleton->setGlobalTransform(transform);
	}
}