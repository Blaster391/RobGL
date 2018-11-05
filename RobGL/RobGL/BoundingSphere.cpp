#include "BoundingSphere.h"
#include "RenderObject.h"
namespace rgl {
	BoundingSphere::BoundingSphere(RenderObject* attachedObject, float radius) : _attachedObject(attachedObject), _radius(radius)
	{
	}
	BoundingSphere::~BoundingSphere()
	{
	}

	bool BoundingSphere::insidePlane(Plane & p)
	{
		return p.sphereInPlane(_attachedObject->getPosition(),_radius);
	}
}