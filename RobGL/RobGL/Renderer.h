#pragma once
#include "glad/glad.h"
#include <Window/Window.h>
#include "RenderPool.h"
#include <vector>
#include "Camera.h"
#include "PostProcessingFX.h"
#include "LightPool.h"
#include "CombinePool.h"
#include "ShadowmapPool.h"
#include "AnimatedRenderObject.h"
#include "SkyboxFX.h"

namespace rgl {
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void enablePostProcessing(const std::vector<Shader*>& toScreenShaders);
		void enableDeferredLighting(const std::vector<Shader*>& lightingShaders, const std::vector<Shader*>& combineShaders, Camera* camera, ScreenInformationUniform* screenInformationUniform);
		void enableShadowMapping(const std::vector<Shader*>& shadowShaders, const std::vector<Shader*>& animatedShadowShaders, Camera* shadowViewport, int shadowMapSize);

		void update(float delta);

		void addLight(PointLight* light);
		void addRenderPool(RenderPool* rp);
		void addPostProcessingFX(PostProcessingFX* fx);

		void addRenderObjectToShadowPool(RenderObject* ro);
		void addAnimatedRenderObjectToShadowPool(AnimatedRenderObject* ro);

		GLuint getShadowMapTexture() { return _shadowTex; }

		Texture* getDepthTexture();
		Texture* getNormalsTexture();
		Texture* getEmissiveTexture();

		void resize(int width, int height);


	private:
		void clearBuffers();
		void swapBuffers();

		void setupLighting(int width, int height);
		void setupShadowMap(int shadowMapSize);
		void setupFramebuffers(int width, int height);
		void bindFrameBuffers();
		void unbindFrameBuffers();

		GLuint createFramebufferTexture(int width, int height, bool depth = false, bool normals = false);

		void freeFramebuffers();

		void drawShadows(float delta);
		void drawLights(float delta);
		void combineLightBuffers(float delta);

		void postProcess(float delta);

		void sendToBackBuffer(float delta);

		std::vector<RenderPool*> _renderPools;
		std::vector<RenderPool*> _uiRenderPools;
		std::vector<PostProcessingFX*> _postFX;

		GLuint _bufferFBO;

		GLuint _shadowFBO;
		GLuint _shadowTex;

		GLuint _lightingFBO;
		GLuint _lightEmissiveTex;
		GLuint _lightSpecularTex;

		GLuint _processFBO;
		GLuint _bufferColourTex[2];
		GLuint _bufferDepthTex;
		GLuint _bufferNormalTex;

		Window _window;
		ToScreenRenderPool* _toScreenRenderPool;
		LightPool* _lightPool;
		CombinePool* _lightCombinePool;
		glm::vec4 _ambientColour;

		bool _postProcess = false;
		bool _shadowMap = false;
		bool _lit = false;

		int _shadowMapSize;
		ShadowmapPool* _shadowmapPool;
		ShadowmapPool* _animatedShadowmapPool;

	};
}

