#include "FixedScreenCamera.h"

namespace rgl {
	glm::mat4x4 FixedScreenCamera::getViewMatrix()
	{
		//Identity
		return glm::mat4x4(1);
	}
	glm::mat4x4 FixedScreenCamera::getProjectionMatrix()
	{
		return  glm::ortho(-1, 1, -1, 1, -1, 1);
	}
}


