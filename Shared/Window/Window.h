#pragma once
#include <External/glfw/glfw3.h>

class Window
{
public:
	static GLFWwindow* window;
	Window();
	~Window();

	void startup();
	void update(float delta);
	void shutdown();

	const int WIDTH = 800;
	const int HEIGHT = 600;
};

