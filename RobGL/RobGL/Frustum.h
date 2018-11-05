#pragma once
#include "Plane.h"
namespace rgl {
	class RenderObject;

	class Frustum
	{
	public:
		Frustum(Plane* planes);
		bool insideFrustum(RenderObject* ro);
		~Frustum();
	private:
		Plane* _planes;
	};

}