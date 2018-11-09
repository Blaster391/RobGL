#pragma once
#include "glad/glad.h"
#include <Window/Window.h>
#include "RenderPool.h"
#include <vector>
#include "Camera.h"

namespace rgl {
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void update(float delta);
		void addRenderPool(RenderPool* rp);


	private:
		void clearBuffers();
		void swapBuffers();

		std::vector<RenderPool*> _renderPools;
		std::vector<RenderPool*> _uiRenderPools;


		Window _window;
	};
}

