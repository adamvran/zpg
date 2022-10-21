#pragma once
#include "ShaderProgram.h"
#include <vector>
#include "lib/glm/glm/vec3.hpp"
#include "lib/glm/glm/detail/type_mat4x3.hpp"
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"
#include "Callback.h"
#include <iostream>


class ShaderProgram;

#define CAMERA_UP glm::vec3(0.f, 1.f, 0.f) ///směr vzhůru
#define CAMERA_FOV glm::radians(40.0f) //jak moc ze široka se na objekt koukáme
#define CAMERA_ZNEAR 0.001f
#define CAMERA_ZFAR 100.0f
#define CAMERA_SPEED 0.9f
#define YAW -90.f;
#define PITCH 0.0f
#define SENSITIVITY 0.1f

class Camera
{
private:
	std::vector<ShaderProgram*> subscibers;
	glm::vec3 eye; //kde je kamera
	glm::vec3 direction; //neboli center
	float ratio;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	///my�� srandy
	float yaw;
	float pitch;
	float sensitivity;

	//pozice posledn�ho framu
	float lastX;
	float lastY;
	bool firstMouse;

public:
	Camera(glm::vec3 eye, glm::vec3 direction, float ratio);
	~Camera();
	void notifyAllObservers();
	void move(GLFWwindow* window, double delta);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void addSubscriber(ShaderProgram* shaderProg);
	void updateViewMatrix(glm::vec3 eye, glm::vec3 distance);
	void updateProjectionMatrix(float ratio);
	void updateViewMatrix();
	void updateDirection(glm::vec3 dir);
	void mouseMove(double xposIn, double yposIn);
	void firstSetMouse(float width, float height);
};

