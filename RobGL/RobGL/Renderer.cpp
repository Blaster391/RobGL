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

	}

	void Renderer::enablePostProcessing(std::vector<Shader*> toScreenShaders) {
		setupFramebuffers(_window.getCurrentWidth(), _window.getCurrentHeight());

		_toScreenRenderPool = new ToScreenRenderPool(toScreenShaders, _bufferColourTex[0]);
		_postProcess = true;
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

		for (auto& pool : _renderPools) {
			pool->draw(delta);
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
	void Renderer::addRenderPool(RenderPool* rp) {
		_renderPools.push_back(rp);
	}

	void Renderer::addPostProcessingFX(PostProcessingFX * fx)
	{
		_postFX.push_back(fx);
	}

	void Renderer::clearBuffers()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		/*glClearStencil(1);*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void Renderer::swapBuffers()
	{
		_window.swapBuffers();
	}
	void Renderer::setupFramebuffers(int width, int height)
	{
		//Depth and stencil buffer
		glGenTextures(1, &_bufferDepthTex);
		glBindTexture(GL_TEXTURE_2D, _bufferDepthTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

		for (int i = 0; i < 2; ++i) {
			glGenTextures(1, &_bufferColourTex[i]);
			glBindTexture(GL_TEXTURE_2D, _bufferColourTex[i]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		glGenFramebuffers(1, &_bufferFBO);
		glGenFramebuffers(1, &_processFBO);


		glBindFramebuffer(GL_FRAMEBUFFER, _bufferFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[0], 0);
		// We can check FBO attachment success using this command !
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "FAILED TO SETUP FRAMEBUFFERS" << std::endl;
			return;
		}

		//These aren't used, but it complains if you try to draw without them
		glBindFramebuffer(GL_FRAMEBUFFER, _processFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _bufferDepthTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _bufferColourTex[1], 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	void Renderer::bindFrameBuffers()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _bufferFBO);
	}
	void Renderer::unbindFrameBuffers()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Renderer::freeFramebuffers()
	{
		glDeleteTextures(2, _bufferColourTex);
		glDeleteTextures(1, &_bufferDepthTex);
		glDeleteFramebuffers(1, &_bufferFBO);
		glDeleteFramebuffers(1, &_processFBO);

	}
	void Renderer::postProcess(float delta)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _processFBO);
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

		_toScreenRenderPool->draw(delta);
	}
}
