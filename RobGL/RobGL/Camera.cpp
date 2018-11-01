#include "Camera.h"

namespace rgl {
	Camera::Camera()
	{

	}


	Camera::~Camera()
	{
	}

	void Camera::setProjectionPerspective(float fov)
	{
		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		projectionMatrix =  glm::perspective(fov, (float)width / (float)height, 0.1f, 10000.0f);
	}

	void Camera::setProjectionOrthographic()
	{

		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		projectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f,  -height / 2.0f, height / 2.0f, 0.1f, 10000.0f);
	}
	glm::mat4x4 Camera::getViewMatrix()
	{
		return 
			glm::rotate(glm::mat4(1.0f), -_pitch, glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), -_yaw, glm::vec3(0, 1, 0)) *
			glm::translate(glm::mat4(1.0f), -_position);
	}
}
