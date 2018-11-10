#pragma once
#include "RenderPool.h"
namespace rgl {
	class ToScreenRenderPool :
		public RenderPool
	{
	public:
		ToScreenRenderPool(std::vector<Shader*> shaders, GLuint colourTex);
		virtual ~ToScreenRenderPool();
	private:
		RenderObject* _quadObject;
		Texture* _quadTexture;
		Mesh* _quadMesh;
	};
}
