#pragma once
#include <stdio.h>
#include <iostream>
#include "lib/glfw/include/GLFW/glfw3.h"

class Callback
{
public:
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static std::pair<double, double> cursor_callback(GLFWwindow* window);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	static bool W_callback(GLFWwindow* window);
	static bool A_callback(GLFWwindow* window);
	static bool S_callback(GLFWwindow* window);
	static bool D_callback(GLFWwindow* window);
	static bool mouseCallbak(GLFWwindow* window);
};

