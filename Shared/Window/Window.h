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
	void setWindowResizeCallback(std::function<void(int width, int height)> func);

	inline bool hasFailed() {
		return _failed;
	}

	inline void swapBuffers() {
		glfwSwapBuffers(_window);
	}

	void onKeyPress(int key, int scancode, int action, int mods);
	void onWindowResize(int width, int height);

	std::pair<double, double> getCursorPosition();

	inline int getCurrentHeight() {

		return _currentHeight;
	}

	inline int getCurrentWidth() {
		glfwGetWindowSize(_window, &_currentWidth, &_currentHeight);
		return _currentWidth;
	}

	void hideCursor() {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void showCursor() {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
private:
	GLFWwindow* _window;

	bool _failed = false;

	const int DEFAULT_WIDTH = 800;
	const int DEFAULT_HEIGHT = 600;

	int _currentHeight = DEFAULT_HEIGHT;
	int _currentWidth = DEFAULT_WIDTH;

	std::function<void(int key, int scancode, int action, int mods)> _keycallback;
	std::function<void(int width, int height)> _windowResizeCallback;
};

