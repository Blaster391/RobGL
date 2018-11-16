#include "DirectionalLightCamera.h"
namespace rgl {


	DirectionalLightCamera::DirectionalLightCamera(glm::vec4 colour, glm::vec3 position, glm::vec3 direction) : Camera()
	{
		_uniformData = new DirectionalLightUniform(colour, position, direction);
	}


	DirectionalLightCamera::~DirectionalLightCamera()
	{
		delete _uniformData;
	}
}