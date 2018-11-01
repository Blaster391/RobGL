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

		inline void setPosition(glm::vec3 position) {
			_position = position;
		}

		void setProjectionPerspective(float fov = 45.0f);
		void setProjectionOrthographic();

		glm::mat4x4 getViewMatrix();
		glm::mat4x4 getProjectionMatrix() { return projectionMatrix; }

		void translate(glm::vec3 v);
		void pitch(float p);
		void yaw(float y);
		void roll(float r);


	private:
		glm::mat4x4 projectionMatrix;

		float _pitch = 0;
		float _yaw = 0;
		glm::vec3 _position;
	};

}


