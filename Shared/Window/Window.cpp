#include "Window.h"



Window::Window()
{
}


Window::~Window()
{
}

GLFWwindow* Window::window;

void Window::startup()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Window::update(float delta)
{
	//while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
}

void Window::shutdown()
{
}
