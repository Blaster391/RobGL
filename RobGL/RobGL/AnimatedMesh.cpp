#include "AnimatedMesh.h"


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
}