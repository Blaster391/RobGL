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

	//16x antialias
	glfwWindowHint(GLFW_SAMPLES, 16);

	_window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "RobGL", nullptr, nullptr);

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, this);

	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))->onKeyPress(key, scancode, action, mods);
	});

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))->onWindowResize(width, height);
	});

	glfwGetFramebufferSize(_window, &_currentWidth, &_currentHeight);

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

std::pair<double, double> Window::getCursorPosition() {
	std::pair<double, double> positions;
	glfwGetCursorPos(_window, &positions.first, &positions.second);
	return positions;
}

void Window::onKeyPress(int key, int scancode, int action, int mods)
{
	_keycallback(key, scancode, action, mods);
}

void Window::onWindowResize(int width, int height)
{
	glfwGetFramebufferSize(_window, &_currentWidth, &_currentHeight);
	_windowResizeCallback(width, height);
}

void Window::setInputCallback(std::function<void(int key, int scancode, int action, int mods)> callback)
{
	_keycallback = callback;
}

void Window::setWindowResizeCallback(std::function<void(int width, int height)> func)
{
	_windowResizeCallback = func;
}
