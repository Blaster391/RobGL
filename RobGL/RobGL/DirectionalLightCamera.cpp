#include "DirectionalLightCamera.h"
namespace rgl {


	DirectionalLightCamera::DirectionalLightCamera(glm::vec4 colour, glm::vec3 direction) : Camera()
	{
		_uniformData = new DirectionalLightUniform(colour, direction, this);
	}


	DirectionalLightCamera::~DirectionalLightCamera()
	{
		delete _uniformData;
	}
}