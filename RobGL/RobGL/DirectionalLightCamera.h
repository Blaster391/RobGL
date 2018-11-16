#pragma once
#include "Camera.h"
#include "DirectionalLightUniform.h"
namespace rgl {
	class DirectionalLightCamera :
		public Camera
	{
	public:
		DirectionalLightCamera(glm::vec4 colour, glm::vec3 direction);
		~DirectionalLightCamera();

		DirectionalLightUniform* getUniformData() { return _uniformData; }
	private:
		DirectionalLightUniform* _uniformData;
	};
}
