#pragma once
#include <External/glm/common.hpp>
namespace rgl {
	class Plane
	{
	public:
		Plane() {};
		Plane(const glm::vec4& normal, bool normalise);
		bool sphereInPlane(const glm::vec3& position, float radius);
		~Plane();
	private:
		glm::vec3 _normal;
		float _distance;
	};

}