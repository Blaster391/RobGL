#pragma once
#include "glad/glad.h"
#include <Window/Window.h>
#include "RenderPool.h"
#include <vector>
#include "Camera.h"
#include "PostProcessingFX.h"

namespace rgl {
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void enablePostProcessing(std::vector<Shader*> toScreenShaders);

		void update(float delta);
		void addRenderPool(RenderPool* rp);
		void addPostProcessingFX(PostProcessingFX* fx);

	private:
		void clearBuffers();
		void swapBuffers();

		void setupFramebuffers(int width, int height);
		void bindFrameBuffers();
		void unbindFrameBuffers();
		void freeFramebuffers();

		void postProcess(float delta);

		void sendToBackBuffer(float delta);

		std::vector<RenderPool*> _renderPools;
		std::vector<RenderPool*> _uiRenderPools;
		std::vector<PostProcessingFX*> _postFX;

		GLuint _bufferFBO;
		GLuint _processFBO;
		GLuint _bufferColourTex[2];
		GLuint _bufferDepthTex;

		Window _window;
		RenderPool* _toScreenRenderPool;

		bool _postProcess = false;
	};
}

