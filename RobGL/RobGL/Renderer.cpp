#include "Renderer.h"
#include <iostream>

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

	Renderer::~Renderer()
	{
	}

	void Renderer::update()
	{
		clearBuffers();


		for (auto& pool : _renderPools) {
			pool->draw();
		}

		glDisable(GL_STENCIL_TEST);

		swapBuffers();
	}
	void Renderer::addRenderPool(RenderPool* rp) {
		_renderPools.push_back(rp);
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
}
