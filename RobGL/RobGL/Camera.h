#pragma once
#include <External/glm/mat4x4.hpp>
#include <External/glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"
#include "Frustum.h"
namespace rgl {
	class Camera
	{
	public:
		Camera();
		~Camera();

		inline void setPosition(glm::vec3 position) {
			_position = position;
		}


		void setProjection(glm::mat4 projection);
		void setProjectionPerspective(float fov = 45.0f);
		void setProjectionOrthographic();

		virtual glm::mat4x4 getViewMatrix();
		virtual glm::mat4x4 getProjectionMatrix() { return _projectionMatrix; }

		void translate(glm::vec3 v);
		void pitch(float p);
		void yaw(float y);
		void roll(float r);

		Frustum getFrustum();

		glm::vec3 getPosition();

	private:
		glm::mat4x4 _projectionMatrix;

		float _pitch = 0;
		float _yaw = 0;
		float _roll = 0;
		glm::vec3 _position;
	};

}


