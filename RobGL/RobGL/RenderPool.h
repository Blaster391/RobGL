#pragma once
#include "RenderObject.h"
#include "Shader.h"
#include <vector>
#include "glad/glad.h"
#include "Camera.h"
#include "Box.h"
#include "BaseUniform.h"

namespace rgl {

	class RenderPool
	{
	public:
		RenderPool(const std::vector<Shader*>& shaders, Camera* c);
		~RenderPool();

		void addRenderObject(RenderObject* r);

		void draw(float delta);

		inline Camera* getCamera() { return _camera; }
		inline void setCamera(Camera* c) { _camera = c; }

		void setScissor(bool active);
		void setScissorBounds(Box b);

		void setEnabled(bool active);


		void addUniformData(BaseUniform* uniform);

	protected:
		void setUniforms();

		std::vector<RenderObject*> _renderObjects;

		std::vector<BaseUniform*> _uniforms;

		Camera* _camera = nullptr;

		GLuint _program;

		bool _enabled = true;

		bool _scissor = false;
		Box _scissorBounds;

		bool _frustumCulling = true;

		bool beginDraw();
		virtual void drawData(float delta);
		void endDraw();

	};
}


