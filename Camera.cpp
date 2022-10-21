#include "Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 direction, float ratio)
{
    this->eye = eye;
    this->direction = direction;
    this->ratio = ratio;

    //first matrix init
    this->viewMatrix = glm::lookAt(this->eye,this->eye + this->direction, CAMERA_UP);
    this->projectionMatrix = glm::perspective(CAMERA_FOV, this->ratio, CAMERA_ZNEAR, CAMERA_ZFAR);

    //mouse settings
    this->yaw = YAW;
    this->pitch = PITCH;
    this->sensitivity = SENSITIVITY;
    this->lastX = 0;
    this->lastY = 0;
    this->firstMouse = true;
}

Camera::~Camera() = default;

void Camera::notifyAllObservers()
{
    for (ShaderProgram* obj : this->subscribers)
    {
        obj->notify(this->viewMatrix, this->projectionMatrix);
    }
}

void Camera::move(GLFWwindow* window, double delta)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float distance = CAMERA_SPEED * (float)delta;

    if (Callback::W_callback(window))
        this->eye += this->direction * distance;
    if (Callback::S_callback(window))
        this->eye -= this->direction * distance;
    if (Callback::A_callback(window))
        this->eye -= glm::normalize(glm::cross(this->direction, CAMERA_UP)) * distance;
    if (Callback::D_callback(window))
        this->eye += glm::normalize(glm::cross(this->direction, CAMERA_UP)) * distance;

    this->updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::addSubscriber(ShaderProgram* shaderProgram)
{
    this->subscribers.push_back(shaderProgram);
}

void Camera::updateViewMatrix(glm::vec3 eye, glm::vec3 distance)
{
    this->eye = eye;
    this->direction = distance;
    this->viewMatrix = glm::lookAt(this->eye, this->eye + this->direction, CAMERA_UP);
}

void Camera::updateProjectionMatrix(float ratio)
{
    this->ratio = ratio;
    this->projectionMatrix = glm::perspective(CAMERA_FOV, this->ratio, CAMERA_ZNEAR, CAMERA_ZFAR);
}

void Camera::updateViewMatrix()
{
    this->viewMatrix = glm::lookAt(this->eye, this->eye + this->direction, CAMERA_UP);
}

void Camera::updateDirection(glm::vec3 dir)
{
    this->direction = dir;
}

void Camera::firstSetMouse(float width, float height)
{
    this->lastX = width / 2;
    this->lastY = height / 2;
}

void Camera::mouseMove(double xPosIn, double yPosIn)
{
    auto xPos = static_cast<float>(xPosIn);
    auto yPos = static_cast<float>(yPosIn);

    if (this->firstMouse)
    {
        this->lastX = xPos;
        this->lastY = yPos;
        this->firstMouse = false;
    }

    float xOffset = xPos - this->lastX;
    float yOffset = this->lastY - yPos;
    this->lastX = xPos;
    this->lastY = yPos;

    xOffset *= this->sensitivity;
    yOffset *= this->sensitivity;

    this->yaw += xOffset;
    this->pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    glm::vec3 dir;
    dir.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    dir.y = sin(glm::radians(this->pitch));
    dir.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->updateDirection(glm::normalize(dir));
    this->updateViewMatrix();
}
