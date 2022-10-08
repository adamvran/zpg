#include "Window.h"
#include <stdlib.h>

Window::Window(int width, int height, const char* title)
{
    this->createWindow(width, height, title);
}

Window::~Window()
{
    glfwDestroyWindow(this->window);
}

void Window::createWindow(int width, int height, const char* title)
{
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window); ///vytvo¯enÌ okna
    glfwSwapInterval(1); ///vytvo¯enÌ okna
}

void Window::windowSize()
{
    int width, height;
    glfwGetFramebufferSize(this->window, &width, &height);
    //float ratio = width / (float)height;
    glViewport(0, 0, width, height);
}

int Window::isWindowClosed()
{
    return glfwWindowShouldClose(this->window);
}

void Window::displayAll()
{
    glfwSwapBuffers(this->window);
}
