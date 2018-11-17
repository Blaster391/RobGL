#include "Plane.h"
#include <External/glm/geometric.hpp>

namespace rgl {

	Plane::Plane(const glm::vec4 & normal, bool normalise)
	{
		if (normalise) {
			float length = glm::length(normal);
			_normal = normal / length;
			_distance = normal.w / length;
		}
		else {
			_normal = normal;
			_distance = normal.w;
		}
	}

	bool Plane::sphereInPlane(const glm::vec3& position, float radius)
	{
		if (glm::dot(position, _normal) + _distance <= -radius) {
				return false;
		}
		return true;
	}

	Plane::~Plane()
	{
	}

	glm::vec3 Plane::getNormal()
	{
		return _normal;
	}
	float Plane::getDistance()
	{
		return _distance;
	}
}