#pragma once
#include "ShaderControll/ShaderProgram.h"
#include <vector>
#include "lib/glm/glm/vec3.hpp"
#include "lib/glm/glm/detail/type_mat4x3.hpp"
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"
#include "Callback.h"
#include "Subject.h"
#include "MatrixType.h"
#include <iostream>


class ShaderProgram;

#define CAMERA_UP glm::vec3(0.f, 1.f, 0.f) //up direction
#define CAMERA_FOV glm::radians(40.0f) //how much wide
#define CAMERA_ZNEAR 0.001f
#define CAMERA_ZFAR 100.0f
#define CAMERA_SPEED 2.f
#define YAW (-90.f)
#define PITCH 0.0f
#define SENSITIVITY 0.1f

class Camera : public Subject
{
private:
	glm::vec3 eye{}; //where is camera
	glm::vec3 direction{}; //center
	float ratio;
	glm::mat4 viewMatrix{};
	glm::mat4 projectionMatrix{};

	//mouse settings
	float yaw;
	float pitch;
	float sensitivity;

	//last frame position
	float lastX;
	float lastY;
	bool firstMouse;

public:
	Camera(glm::vec3 eye, glm::vec3 direction, float ratio);
	~Camera();

    __attribute__((unused)) void notifyAllObservers();
    void notifyAll() override;
    void notifyAll(MatrixType type);
	void move(GLFWwindow* window, double delta);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void addSubscriber(ShaderProgram* shaderProgram);

    __attribute__((unused)) void removeSubscriber(ShaderProgram *shaderProgram);

    __attribute__((unused)) void updateViewMatrix(glm::vec3 eye_, glm::vec3 distance);
	void updateProjectionMatrix(float ratio_);
	void updateViewMatrix();
	void updateDirection(glm::vec3 dir);

    __attribute__((unused)) void mouseMove(double xposIn, double yposIn);
    void mouseMove(double xposIn, double yposIn, bool isMousePressed);
    void firstSetMouse(float width, float height);

    __attribute__((unused)) glm::vec3 getEye();
    glm::vec3 getDirection();

};
