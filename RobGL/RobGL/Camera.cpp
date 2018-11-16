#include "Camera.h"
#include "Plane.h"

namespace rgl {
	Camera::Camera()
	{

	}


	Camera::~Camera()
	{
	}

	void Camera::setProjection(glm::mat4 projection)
	{
		_projectionMatrix = projection;
	}

	void Camera::setProjectionPerspective(float n, float f, float fov)
	{
		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		_projectionMatrix =  glm::perspective(fov, (float)width / (float)height, n, f);
	}

	void Camera::setProjectionOrthographic()
	{

		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		_projectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f,  -height / 2.0f, height / 2.0f, 0.1f, 10.0f);
	}
	glm::mat4x4 Camera::getViewMatrix()
	{
		return 
			glm::rotate(glm::mat4(1.0f), -_pitch, glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), -_yaw, glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1.0f), -_roll, glm::vec3(0, 0, 1)) *
			glm::translate(glm::mat4(1.0f), -_position);
	}

	void Camera::translate(glm::vec3 v) {
		_position += v;
	}

	void Camera::pitch(float p) {
		_pitch += p;
	}

	void Camera::yaw(float y) {
		_yaw += y;
	}

	void Camera::roll(float r)
	{
		_roll += r;
	}

	Frustum Camera::getFrustum()
	{

		glm::mat4x4 vpMatrix =  getProjectionMatrix() * getViewMatrix();
		Plane planes[6];

		glm::vec4 xaxis(vpMatrix[0][0], vpMatrix[1][0], vpMatrix[2][0], vpMatrix[3][0]);
		glm::vec4 yaxis(vpMatrix[0][1], vpMatrix[1][1], vpMatrix[2][1], vpMatrix[3][1]);
		glm::vec4 zaxis(vpMatrix[0][2], vpMatrix[1][2], vpMatrix[2][2], vpMatrix[3][2]);
		glm::vec4 waxis(vpMatrix[0][3], vpMatrix[1][3], vpMatrix[2][3],vpMatrix[3][3]);
		
		// RIGHT
		auto result = waxis - xaxis;
		planes[0] = Plane((waxis - xaxis), true);

		// LEFT
		auto result2 = waxis + xaxis;
		planes[1] = Plane((waxis + xaxis), true);

		// BOTTOM
		auto result3 = waxis + yaxis;
		planes[2] = Plane((waxis + yaxis), true);

		 // TOP
		auto result4 = waxis - yaxis;
		planes[3] = Plane((waxis - yaxis), true);

		 // FAR
		auto result5 = waxis - zaxis;
		planes[4] = Plane((waxis - zaxis), true);

		 // NEAR
		auto result6 = waxis + zaxis;
		planes[5] = Plane((waxis + zaxis), false);


		Frustum f(planes);

		return f;
	}

	glm::vec3 Camera::getPosition()
	{
		return _position;
	}
}
