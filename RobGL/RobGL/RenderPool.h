#pragma once
#include "RenderObject.h"
#include "Shader.h"
#include <vector>
#include "glad/glad.h"
#include "Camera.h"

namespace rgl {
	//TODO split into more classes - make it "CameraRenderPool"/"UI Render Pool" etc
	class RenderPool
	{
	public:
		RenderPool(const std::vector<Shader*>& shaders, Camera* c);
		~RenderPool();

		void addRenderObject(RenderObject* r);

		void draw();

		inline Camera* getCamera() { return _camera; }
		inline void setCamera(Camera* c) { _camera = c; }

	private:
		void setUniforms();

		std::vector<RenderObject*> _renderObjects;

		Camera* _camera = nullptr;

		GLuint _program;
	};
}


