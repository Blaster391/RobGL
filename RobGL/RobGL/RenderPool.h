#pragma once
#include "RenderObject.h"
#include "Shader.h"
#include <vector>
#include "glad/glad.h"
#include "Camera.h"
#include "Box.h"

namespace rgl {
	//TODO split into more classes - make it "CameraRenderPool"/"UI Render Pool" etc
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


	protected:
		void setUniforms();

		std::vector<RenderObject*> _renderObjects;

		Camera* _camera = nullptr;

		GLuint _program;

		bool _enabled = true;

		bool _scissor = false;
		Box _scissorBounds;

		GLuint _viewMatrixPosition;
		GLuint _projectionMatrixPosition;

		bool _frustumCulling = true;

		bool beginDraw();
		virtual void drawData(float delta);
		void endDraw();

	};
}


