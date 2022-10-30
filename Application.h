#pragma once
#include "Scene.h"
#include "Models.h"

class Application
{
private:
	Scene* scene{};

public:
	Application(int width, int height, const char* title);
	~Application();
	void createScene(int width, int height, const char* title);
	void run();

	void transformObject(int objectInArray, float angle, glm::vec3 vector);
	void transformObject(int objectInArray, TransformationType type, glm::vec3 vector);

	//Camera
	void createCamera(glm::vec3 eye, glm::vec3 dir);

    int createNewObject(Models *model, const char *vertexDefinition, const char *fragmentDefinition);
};


