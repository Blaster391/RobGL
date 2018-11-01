#pragma once
#include <External/glfw/glfw3.h>
#include <functional>
class Window
{
public:

	Window();
	~Window();

	void startup();
	void update(float delta);
	void shutdown();

	bool ShouldClose();

	void setInputCallback(std::function<void(int, int, int, int)> func);

	inline bool hasFailed() {
		return _failed;
	}

	inline void swapBuffers() {
		glfwSwapBuffers(_window);
	}

	void onKeyPress(int key, int scancode, int action, int mods);
	std::pair<double, double> getCursorPosition();

	//TODO better
	inline int getCurrentHeight() {
		int width, height;
		glfwGetWindowSize(_window,&width, &height);
		return height;
	}

	inline int getCurrentWidth() {
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		return width;
	}

private:
	GLFWwindow* _window;

	bool _failed = false;

	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::function<void(int key, int scancode, int action, int mods)> keycallback;
};

