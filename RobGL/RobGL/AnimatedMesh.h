#pragma once
#include "Mesh.h"
#include "VertexWeightData.h"
#include "Skeleton.h"
namespace rgl {
	class AnimatedMesh : public Mesh
	{
	public:
		AnimatedMesh();
		~AnimatedMesh();

		void setVerticiesWeightData(std::vector<VertexWeightData> data);
		std::vector<VertexWeightData> getVerticiesWeightData();
		void setSkeleton(Skeleton* sk);

		virtual void draw(GLuint program) override;

		virtual void buffer() override;

		void setGlobalTransform(glm::mat4 transform);

	private:
		std::vector<VertexWeightData> _verticiesWeightData;
		Skeleton* _skeleton;
		GLuint weightBuffer;

	};
}
