#include "Renderer.h"
#include <iostream>
#include "ToScreenRenderPool.h"


namespace rgl {

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	Renderer::Renderer(Window & window) : _window(window)
	{
		auto success = gladLoadGL();
		if (!success) {
			std::cout << "Error loading glad" << std::endl;
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);


		//TODO configuations
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);


	}

	void Renderer::enablePostProcessing(std::vector<Shader*> toScreenShaders) {
		setupFramebuffers(_window.getCurrentWidth(), _window.getCurrentHeight());

		_toScreenRenderPool = new ToScreenRenderPool(toScreenShaders, _bufferColourTex[0]);
		_postProcess = true;
	}

	void Renderer::enableDeferredLighting(std::vector<Shader*>& lightingShaders, std::vector<Shader*>& combineShaders, Camera* camera)
	{
		glDisable(GL_DEPTH_TEST);
		_lit = true;
		if (!_postProcess) {
			std::cout << "Post processing must be enabled for lighting to function correctly!" << std::endl;
		}
		_lightPool = new LightPool(lightingShaders, camera, _bufferDepthTex, _bufferNormalTex);
		_lightCombinePool = new CombinePool(combineShaders,_bufferColourTex[0],_lightEmissiveTex, _lightSpecularTex);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::enableShadowMapping(std::vector<Shader*>& shadowShaders, Camera * shadowViewport, int shadowMapSize)
	{
		setupShadowMap(shadowMapSize);
		_shadowmapPool = new ShadowmapPool(shadowShaders, shadowViewport);
	}


	Renderer::~Renderer()
	{
		if (_postProcess) {
			freeFramebuffers();
			delete _toScreenRenderPool;
		}
	}

	void Renderer::update(float delta)
	{
		if (_postProcess) {
			bindFrameBuffers();
		}

		clearBuffers();

		if (_shadowMap) {
			drawShadows(delta);
		}

		for (auto& pool : _renderPools) {
			pool->draw(delta);
		}

		if (_lit) {
			glDisable(GL_DEPTH_TEST);
			drawLights(delta);

			combineLightBuffers(delta);
			glEnable(GL_DEPTH_TEST);

		}

		if (_postProcess) {
			unbindFrameBuffers();
			glDisable(GL_DEPTH_TEST);

			postProcess(delta);
			sendToBackBuffer(delta);

			glEnable(GL_DEPTH_TEST);
		}

		glDisable(GL_STENCIL_TEST);

		swapBuffers();
	}

	void Renderer::setAmbientColour(glm::vec4 colour)
	{
		_ambientColour = colour;
	}
	void Renderer::addLight(PointLight * light)
	{
		if (_lit) {
			_lightPool->addLight(light);
		}
	}
	void Renderer::addRenderPool(RenderPool* rp) {
		_renderPools.push_back(rp);
	}

	void Renderer::addPostProcessingFX(PostProcessingFX * fx)
	{
		_postFX.push_back(fx);
	}

	void Renderer::addRenderObjectToShadowPool(RenderObject * ro)
	{
		_shadowmapPool->addRenderObject(ro);
	}

	Texture * Renderer::getDepthTexture()
	{
		return new Texture(_bufferDepthTex,false);
	}

	void Renderer::clearBuffers()
	{
		/*glClearStencil(1);*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void Renderer::swapBuffers()
	{
		_window.swapBuffers();
	}

	void Renderer::setupLighting(int width, int height)
	{
		_lightEmissiveTex = createFramebufferTexture(width, height, false);
		_lightSpecularTex = createFramebufferTexture(width, height, false);

		GLuint drawBuffers[2] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 };

		glGenFramebuffers(1, &_lightingFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, _lightingFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _lightEmissiveTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _lightSpecularTex, 0);
		glDrawBuffers(2, drawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "FAILED TO SETUP LIGHT BUFFERS" << std::endl;
			return;
		}
	}

	void Renderer::setupShadowMap(int shadowMapSize)
	{
		_shadowMapSize = shadowMapSize;

		glGenTextures(1, &_shadowTex);
		glBindTexture(GL_TEXTURE_2D, _shadowTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _shadowMapSize, _shadowMapSize,0, GL_DEPTH_COMPONENT,GL_FLOAT,nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &_shadowFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, _shadowFBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowTex, 0);
		glDrawBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::setupFramebuffers(int width, int height)
	{
		setupLighting(width, height);

		//Depth and stencil buffer
		_bufferDepthTex = createFramebufferTexture(width, height, true);


		for (int i = 0; i < 2; ++i) {
			_bufferColourTex[i] = createFramebufferTexture(width, height, false);
		}

		_bufferNormalTex = createFramebufferTexture(width, height, false, true);

		GLuint drawBuffers[4] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

		glGenFramebuffers(1, &_bufferFBO);
		glGenFramebuffers(1, &_processFBO);

		glBindFramebuffer(GL_FRAMEBUFFER, _bufferFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[0], 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _bufferNormalTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _lightEmissiveTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _lightSpecularTex, 0);
		glDrawBuffers(4, drawBuffers);

		// We can check FBO attachment success using this command !
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "FAILED TO SETUP FRAMEBUFFERS" << std::endl;
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, _processFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[1], 0);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _bufferNormalTex, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	void Renderer::bindFrameBuffers()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _bufferFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[0], 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _bufferNormalTex, 0);
	}
	void Renderer::unbindFrameBuffers()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	GLuint Renderer::createFramebufferTexture(int width, int height, bool depth, bool normals)
	{
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (depth) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		}
		else if (normals) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_HALF_FLOAT, nullptr);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		return tex;
	}
	void Renderer::freeFramebuffers()
	{
		glDeleteTextures(2, _bufferColourTex);
		glDeleteTextures(1, &_bufferDepthTex);
		glDeleteFramebuffers(1, &_bufferFBO);
		glDeleteFramebuffers(1, &_processFBO);

	}
	void Renderer::drawShadows(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _shadowFBO);
		glViewport(0, 0, _shadowMapSize, _shadowMapSize);
		_shadowmapPool->draw(delta);
		glViewport(0, 0, _window.getCurrentWidth(), _window.getCurrentHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::drawLights(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _lightingFBO);
		_lightPool->draw(delta);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void Renderer::combineLightBuffers(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _bufferFBO);
		_lightCombinePool->draw(delta);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::postProcess(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _processFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[1], 0);
		//glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		for (auto& fx : _postFX) {
			fx->process(delta, _bufferColourTex[0], _bufferColourTex[1]);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	void Renderer::sendToBackBuffer(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		_toScreenRenderPool->setRenderTexture(_bufferColourTex[0]);
		_toScreenRenderPool->draw(delta);
	}
}
