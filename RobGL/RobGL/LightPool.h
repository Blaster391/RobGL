#pragma once
#include "RenderPool.h"
#include "PointLight.h"
#include "ScreenInformationUniform.h"
namespace rgl {
	class LightPool : public RenderPool
	{
	public:
		LightPool(const std::vector<Shader*>& shaders, Camera* c, ScreenInformationUniform* screenInfoUnform, GLuint depthTex, GLuint normalsTex);
		~LightPool();

		void addLight(PointLight* light);

		virtual void drawData(float delta) override;
	private:

		std::vector<PointLight*> _lights;
		GLuint _depthTex;
		GLuint _normalsTex;
	};
}
