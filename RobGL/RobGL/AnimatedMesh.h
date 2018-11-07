#pragma once
#include "Mesh.h"
#include "VertexWeightData.h"
namespace rgl {
	class AnimatedMesh : public Mesh
	{
	public:
		AnimatedMesh();
		~AnimatedMesh();

		void setVerticiesWeightData(std::vector<VertexWeightData> data);
		std::vector<VertexWeightData> getVerticiesWeightData();

	private:
		std::vector<VertexWeightData> _verticiesWeightData;

	};
}
