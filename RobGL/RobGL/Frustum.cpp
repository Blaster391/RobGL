#include "Frustum.h"
#include "RenderObject.h"
namespace rgl {


	Frustum::Frustum(Plane * planes)
		: _planes(new Plane[6])
	{
		for (int i = 0; i < 6; ++i) {
			_planes[i] = planes[i];
		}
	}

	bool Frustum::insideFrustum(RenderObject* ro)
	{
		auto bounds = ro->getBounds();
		//If no bounds set, assume inside
		if (bounds == nullptr) {
			return true;
		}

		for (int i = 0; i < 6; ++i) {
			{
				if (!bounds->insidePlane(_planes[i])) {
					return false;
				}
			}
		}

		return true;
	}

	Frustum::~Frustum()
	{
		//delete[] _planes;
	}
}