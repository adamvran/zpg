#pragma once
#include "Scene.h"

class Application
{
private:
	Scene* scene{};

public:
	Application(int width, int height, const char* title);
	~Application();
	void createScene(int width, int height, const char* title);
	void run();

    __attribute__((unused)) void transformObject(int objectInArray, float angle, glm::vec3 vector);
	void transformObject(int objectInArray, TransformationType type, glm::vec3 vector);

	//Camera
	void createCamera(glm::vec3 eye, glm::vec3 dir);

    u_long createNewObject(Models *model, const char *vertexDefinition, const char *fragmentDefinition);
    void createLights(LightType type);

};


