#include "Callback.h"
#include "lib/glm/glm/vec3.hpp"
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "lib/glm/glm/ext/matrix_projection.hpp"

void Callback::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
/*
void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Callback::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Callback::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}
*/
std::pair<double, double> Callback::cursor_callback(GLFWwindow* window)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return std::make_pair(xPos, yPos);
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
        printf("button_callback [%d,%d,%d]\n", button, action, mode);
    }
}

bool Callback::W_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
}

bool Callback::A_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
}

bool Callback::S_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
}

bool Callback::Q_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
}

bool Callback::D_callback(GLFWwindow* window)
{
	return (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
}

bool Callback::mouseCallbackLeft(GLFWwindow* window)
{
    return (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
}
bool Callback::mouseCallbackRight(GLFWwindow* window)
{
    return (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
}

void Callback::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

void Callback::window_focus_callback(GLFWwindow *window, int focused) {

}

void Callback::window_iconify_callback(GLFWwindow *window, int iconified) {

}

void Callback::window_size_callback(GLFWwindow *window, int width, int height) {

}
