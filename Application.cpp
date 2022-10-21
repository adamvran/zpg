#include "Application.h"

Application::Application(int width, int height, const char* title)
{
	this->createScene(width, height, title);
}

Application::~Application()
{
	this->scene->~Scene();
}

void Application::createScene(int width, int height, const char* title)
{
	this->scene = new Scene(width, height, title);
}

void Application::run()
{
	this->scene->run();
}

int Application::createNewObject(int countVBO, float* points, int sizeOfPoints, int countVAO, pair<int, int> indexArray,
                                 int vertexCount, GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer,
                                 const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType,
                                 int countOfVertex)
{
	return this->scene->createAndAdd(countVBO, points, sizeOfPoints, countVAO, indexArray, vertexCount, vertexOffset,
                                     pointer, vertexDefinition, fragmentDefinition, objectType, countOfVertex);
}

void Application::transformObject(int objectInArray, float angle, glm::vec3 vector)
{
	this->scene->transform(objectInArray, angle, vector);
}

void Application::transformObject(int objectInArray, TransformationType type, glm::vec3 vector)
{
	this->scene->transform(objectInArray, type, vector);
}

void Application::createCamera(glm::vec3 eye, glm::vec3 dir)
{
	this->scene->createCamera(eye, dir);
}

