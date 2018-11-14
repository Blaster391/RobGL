#pragma once
#include "PostProcessingFX.h"
#include "Cubemap.h"
namespace rgl {
	class SkyboxFX :
		public PostProcessingFX
	{
	public:
		SkyboxFX(std::vector<Shader*> shaders, Cubemap* skyboxTex, Camera* perspective);
		~SkyboxFX();

		virtual void process(float delta, GLuint& displayTex, GLuint& processTex) override;
	private:
		Cubemap* _skyboxTex;
		Camera* _perspective;
	};
}

