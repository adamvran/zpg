#include "Application.h"

#include <utility>
#include "Models/Models.h"

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

__attribute__((unused)) void Application::transformObject(int objectInArray, float angle, glm::vec3 vector)
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
u_long Application::createNewObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition)
{
    return this->scene->createAndAdd(model, vertexDefinition, fragmentDefinition);
}
u_long Application::createNewObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::string path)
{
    return this->scene->createAndAdd(model, vertexDefinition, fragmentDefinition, std::move(path));
}

u_long Application::createNewObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::vector<std::string> paths)
{
    return this->scene->createAndAdd(model, vertexDefinition, fragmentDefinition, std::move(paths));
}


void Application::createLights(LightType type)
{
    this->scene->createLights(type);
}

