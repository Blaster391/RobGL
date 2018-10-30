#pragma once
#include <Window/Window.h>

namespace rgl {
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();
	private:
		Window _window;
	};
}

