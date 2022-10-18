#include "Window.h"
#include <stdlib.h>

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
	this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window); ///vytvo�en� okna
	glfwSwapInterval(1); ///vytvo�en� okna
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
	//int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	return (width / (float)height);
}

float Window::getWidth()
{
	return this->width;
}

float Window::getHeight()
{
	return this->height;
}
