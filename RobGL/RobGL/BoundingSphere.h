#pragma once
#include "Plane.h"

namespace rgl {
	class RenderObject;

	class BoundingSphere
	{
	public:
		BoundingSphere(RenderObject* attachedObject, float radius);
		~BoundingSphere();

		bool insidePlane(Plane& p);
	private:
		float _radius;
		RenderObject* _attachedObject;
	};

}