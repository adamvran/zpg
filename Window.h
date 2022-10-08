#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
class Window
{
private:
    GLFWwindow* window{};
public:
    Window(int width, int height, const char* title);
    ~Window();
    void createWindow(int width, int height, const char* title);
    void windowSize();
    int isWindowClosed();
    void displayAll();
};

