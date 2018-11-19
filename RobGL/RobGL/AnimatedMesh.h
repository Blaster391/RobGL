#pragma once
#include "Mesh.h"
#include "VertexWeightData.h"
#include "Skeleton.h"
#include "Animation.h"
namespace rgl {
	class AnimatedMesh : public Mesh
	{
	public:
		AnimatedMesh();
		~AnimatedMesh();

		void setVerticiesWeightData(std::vector<VertexWeightData> data);
		std::vector<VertexWeightData> getVerticiesWeightData();
		
		void setSkeleton(Skeleton* sk);
		void setAnimations(std::vector<Animation> animations);



		virtual void draw(float delta, GLuint program) override;

		virtual void buffer() override;


		Skeleton* generateSkeleton();

		Animation getAnimation(int animation);

	private:
		std::vector<VertexWeightData> _verticiesWeightData;
		std::vector<Animation> _animations;

		Skeleton* _baseSkeleton;

		GLuint weightBuffer;

	};
}
