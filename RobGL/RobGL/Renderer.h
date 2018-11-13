#pragma once
#include "glad/glad.h"
#include <Window/Window.h>
#include "RenderPool.h"
#include <vector>
#include "Camera.h"
#include "PostProcessingFX.h"
#include "LightPool.h"
#include "CombinePool.h"

namespace rgl {
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void enablePostProcessing(std::vector<Shader*> toScreenShaders);
		void enableLighting(std::vector<Shader*>& lightingShaders, std::vector<Shader*>& combineShaders, Camera* camera);

		void update(float delta);

		void setAmbientColour(glm::vec4 colour);
		void addLight(PointLight* light);
		void addRenderPool(RenderPool* rp);
		void addPostProcessingFX(PostProcessingFX* fx);



	private:
		void clearBuffers();
		void swapBuffers();

		void setupLighting(int width, int height);
		void setupFramebuffers(int width, int height);
		void bindFrameBuffers();
		void unbindFrameBuffers();

		GLuint createFramebufferTexture(int width, int height, bool depth);

		void freeFramebuffers();

		void drawLights(float delta);
		void combineBuffers(float delta);

		void postProcess(float delta);

		void sendToBackBuffer(float delta);

		std::vector<RenderPool*> _renderPools;
		std::vector<RenderPool*> _uiRenderPools;
		std::vector<PostProcessingFX*> _postFX;

		GLuint _bufferFBO;

		GLuint _lightingFBO;
		GLuint _lightEmissiveTex;
		GLuint _lightSpecularTex;

		GLuint _processFBO;
		GLuint _bufferColourTex[2];
		GLuint _bufferDepthTex;
		GLuint _bufferNormalTex;

		Window _window;
		RenderPool* _toScreenRenderPool;
		LightPool* _lightPool;
		CombinePool* _combinePool;
		glm::vec4 _ambientColour;

		bool _postProcess = false;
		bool _lit = false;
	};
}

