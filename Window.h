#pragma once
#include "lib/glfw/include/GLFW/glfw3.h"

class Window
{
private:
	GLFWwindow* window{};
	int width;
	int height;
	const char* title;
public:
	Window(int width, int height, const char* title);
	~Window();
	void createWindow();
	void windowSize();
	int isWindowClosed();
	void displayAll();

	GLFWwindow* getWindow();
	float getRatio();
	float getWidth() const;
	float getHeight() const;
};

