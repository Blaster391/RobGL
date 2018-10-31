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

	void onKeyPress(int, int, int, int);


private:
	GLFWwindow* _window;

	bool _failed = false;

	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::function<void(int key, int scancode, int action, int mods)> keycallback;
};

