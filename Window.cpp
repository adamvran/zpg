#include "Window.h"
#include <cstdlib>

Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->createWindow();
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}

void Window::createWindow()
{
	this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);
}

void Window::windowSize()
{
	//int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	//float ratio = width / (float)height;
	//glViewport(0, 0, width, height);
}

int Window::isWindowClosed()
{
	return glfwWindowShouldClose(this->window);
}

void Window::displayAll()
{
	glfwSwapBuffers(this->window);
}

GLFWwindow* Window::getWindow()
{
	return this->window;
}

float Window::getRatio()
{
	glfwGetFramebufferSize(this->window, &width, &height);
	return ((float)width / (float)height);
}

float Window::getWidth() const
{
	return (float)this->width;
}

float Window::getHeight() const
{
	return (float)this->height;
}
