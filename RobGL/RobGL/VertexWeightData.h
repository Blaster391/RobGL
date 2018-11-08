#pragma once
#include <External/glm/common.hpp>
#include <External/glm/gtc/type_precision.hpp>
namespace rgl {
	struct VertexWeightData
	{
	public:
		glm::vec4 Joints;
		glm::vec4 Weights;
	};
}
