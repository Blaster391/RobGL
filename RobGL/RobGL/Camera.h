#pragma once
#include <External/glm/mat4x4.hpp>
#include <External/glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"
namespace rgl {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void setPerspective();
		void setOrthographic();

		glm::mat4x4 getViewMatrix();
		glm::mat4x4 getProjectionMatrix() { return projectionMatrix; }

	private:
		glm::mat4x4 projectionMatrix;
		float _pitch;
		float _yaw;
		glm::vec3 _position;
	};

}


