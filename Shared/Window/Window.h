#pragma once
#include <External/glfw/glfw3.h>

class Window
{
public:

	Window();
	~Window();

	void startup();
	void update(float delta);
	void shutdown();

	bool ShouldClose();

	inline bool hasFailed() {
		return _failed;
	}

	inline void swapBuffers() {
		glfwSwapBuffers(_window);
	}

private:
	GLFWwindow* _window;

	bool _failed = false;

	const int WIDTH = 800;
	const int HEIGHT = 600;
};

