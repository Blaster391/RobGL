#pragma once
#include "Plane.h"
#include "RenderObject.h"
namespace rgl {

	class Frustum
	{
	public:
		Frustum(Plane* planes);
		bool insideFrustum(RenderObject* ro);
		bool insideFrustum(glm::vec3 position);
		~Frustum();
	protected:
		Plane* _planes;
	};
}