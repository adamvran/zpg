#include "Window.h"
#include <cstdlib>

Window::Window(int width, int height) {
    this->window = glfwCreateWindow(width, height, "ZPG", nullptr, nullptr);
    if (!this->window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}
Window::~Window() {
    glfwDestroyWindow(this->window);
}

void Window::windowSize(){
    int width, height;
    glfwGetFramebufferSize(this->window, &width, &height);
    //float ratio = width / (float)height;
    glViewport(0, 0, width, height);
}

int Window::windowClosed(){
    return glfwWindowShouldClose(this->window);
}

void Window::renderWindow(){
    glfwSwapBuffers(this->window);
}
