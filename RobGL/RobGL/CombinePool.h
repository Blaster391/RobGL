#pragma once
#include "RenderPool.h"
namespace rgl {
	class CombinePool : public RenderPool
	{
	public:
		CombinePool(const std::vector<Shader*>& shaders, GLuint& bufferColourTex, GLuint emissiveTex, GLuint specularTex);
		~CombinePool();


		virtual void drawData(float delta) override;
	protected:
		RenderObject* _quadObject;
		Texture* _quadTexture;
		Mesh* _quadMesh;
		GLuint& _bufferColourTex;
		GLuint _emissiveTex;
		GLuint _specularTex;
	};

}