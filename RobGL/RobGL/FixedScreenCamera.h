#pragma once
#include "Camera.h"
namespace rgl {
	class FixedScreenCamera
		: public Camera
	{
	public:
		virtual glm::mat4x4 getViewMatrix() override;
		virtual glm::mat4x4 getProjectionMatrix() override;
	};
}


