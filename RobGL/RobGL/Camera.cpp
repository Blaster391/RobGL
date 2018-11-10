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

	void Camera::setProjectionPerspective(float fov)
	{
		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		_projectionMatrix =  glm::perspective(fov, (float)width / (float)height, 0.1f, 100.0f);
	}

	void Camera::setProjectionOrthographic()
	{

		//TODO remove hardcoded stuffs
		int width = 800;
		int height = 600;
		_projectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f,  -height / 2.0f, height / 2.0f, 0.1f, 10000.0f);
	}
	glm::mat4x4 Camera::getViewMatrix()
	{
		return 
			glm::rotate(glm::mat4(1.0f), -_pitch, glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), -_yaw, glm::vec3(0, 1, 0)) *
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

		glm::vec4 xaxis(vpMatrix[0]);
		glm::vec4 yaxis(vpMatrix[1]);
		glm::vec4 zaxis(vpMatrix[2]);
		glm::vec4 waxis(vpMatrix[3]);
		
		// RIGHT
		planes[0] = Plane((waxis - xaxis), true);

		// LEFT
		planes[1] = Plane((waxis + xaxis), true);

		// BOTTOM
		planes[2] = Plane((waxis + yaxis), true);

		 // TOP
		planes[3] = Plane((waxis - yaxis), true);

		 // FAR
		planes[4] = Plane((waxis - zaxis), true);

		 // NEAR
		planes[5] = Plane((waxis + zaxis), true);


		Frustum f(planes);

		return f;
	}
}
