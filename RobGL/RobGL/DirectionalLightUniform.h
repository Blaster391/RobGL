#pragma once
#include "BaseUniform.h"
#include <External/glm/glm.hpp>

namespace rgl {
	class DirectionalLightUniform :
		public BaseUniform
	{
	public:
		DirectionalLightUniform(glm::vec4 colour, glm::vec3 position, glm::vec3 direction);
		~DirectionalLightUniform();

		virtual void apply(GLuint program) override;
	private:
		glm::vec4 _colour;
		glm::vec3 _position;
		glm::vec3 _direction;

	};
}
