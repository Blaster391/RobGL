#include "Camera.h"

namespace rgl {
	Camera::Camera()
	{

	}


	Camera::~Camera()
	{
	}

	void Camera::setPerspective()
	{
		projectionMatrix = = Matrix4::Perspective(0.1f, 10000.0f, (float)width / (float)height, 45.0f);
	}

	void Camera::setOrthographic()
	{
		projectionMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);
	}
	glm::mat4x4 Camera::getViewMatrix()
	{
		glm::mat4x4 view;

		return glm::rotate(view , -_pitch, glm::vec3(1, 0, 0)) *
				glm::rotate(view , -_yaw, glm::vec3(0, 1, 0)) *
				glm::translate(view,-_position);
	}
}
