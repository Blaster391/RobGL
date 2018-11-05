#include "Plane.h"
#include <External/glm/geometric.hpp>
namespace rgl {

	Plane::Plane(const glm::vec3 & normal, float distance, bool normalise)
	{
		if (normalise) {			float length = sqrt(glm::dot(normal, normal));			_normal = normal / length;
			_distance = distance / length;
		}
		else {
			_normal = normal;
			_distance = distance;
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
}