#pragma once
#include "BaseUniform.h"
#include <External/glm/glm.hpp>

namespace rgl {
	class DirectionalLightUniform :
		public BaseUniform
	{
	public:
		DirectionalLightUniform(glm::vec4 colour, glm::vec3 position, glm::mat4 rotation);
		~DirectionalLightUniform();

		virtual void apply(GLuint program) override;
	private:
		glm::vec4 _colour;
		glm::vec3 _position;
		glm::mat4 _rotation;

	};
}
