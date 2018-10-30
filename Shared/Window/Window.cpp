#include "Window.h"
#include <iostream>


void errorCallback(int error, const char* description)
{
	std::cout << "Error: " << description << std::endl;
}

Window::Window()
{
}


Window::~Window()
{
}

void Window::startup()
{
	_failed = !glfwInit();

	if (_failed) {
		return;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//4x antialias
	glfwWindowHint(GLFW_SAMPLES, 16);

	_window = glfwCreateWindow(WIDTH, HEIGHT, "RobGL", nullptr, nullptr);

	glfwMakeContextCurrent(_window);

	_failed = !_window;
}

void Window::update(float delta)
{
	//while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
}

void Window::shutdown()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}


bool Window::ShouldClose() {
	return glfwWindowShouldClose(_window);
}