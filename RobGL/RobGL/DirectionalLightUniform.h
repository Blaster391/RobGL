#pragma once
#include "BaseUniform.h"
#include <External/glm/glm.hpp>

namespace rgl {
	class Camera;

	class DirectionalLightUniform :
		public BaseUniform
	{
	public:
		DirectionalLightUniform(glm::vec4 colour, glm::vec3 direction, Camera* shadowPositionCamera);
		~DirectionalLightUniform();

		virtual void apply(GLuint program) override;

		void setShadowTexture(GLuint shadowTex) {
			_shadowTex = shadowTex;
		}

	private:
		glm::vec4 _colour;
		glm::vec3 _direction;

		Camera* _shadowCamera;
		GLuint _shadowTex;
	};
}
