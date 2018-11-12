#pragma once
#include "RenderPool.h"
#include "PointLight.h"
namespace rgl {
	class LightPool : RenderPool
	{
	public:
		LightPool(const std::vector<Shader*>& shaders, Camera* c, GLuint depthTex, GLuint normalsTex);
		~LightPool();

		void addLight(PointLight* light);

		virtual void draw(float delta) override;
	private:

		std::vector<PointLight*> _lights;
		GLuint _depthTex;
		GLuint _normalsTex;
	};
}
