#pragma once
#include "RenderedObject.h"
#include "Window.h"
#include <vector>
#include "Callback.h"
#include "Transformations/TransformationType.h"
#include "Camera.h"
#include <algorithm>
#include <iostream>
#include "Lights/Light.h"
#include "Colors.h"
#include "Models/Models.h"
#include "Lights/LightType.h"
#include "MatrixType.h"



class Scene
{
private:
	Window* window;
	vector<RenderedObject*> renderedObjects;
	Camera* camera{};
    vector<Light*> lights;
    vector<PointLight*> pointLights;
    vector<SpotLight*> spotLights;
    vector<DirectionalLight*> dirLights;
    int indexTexture = 0;


public:
	Scene(int width, int height, const char* title);
	~Scene();

	static void initGLFW();
	static void initGLEW();
    static void initOpenGLVersion();
    void initMouse();
	static void printVersionInfo();
	int isWindowClosed();
	void drawOntoWindow();

	void addRenderedObject(RenderedObject* obj);

	void transform(int objectInArray, float angle, glm::vec3 vector);
	void transform(int objectInArray, TransformationType type, glm::vec3 vector);

	void run();

	void createCamera(glm::vec3 eye, glm::vec3 dir);

    void createLights(LightType type);
    void createLights();
    void createPointLights();
    void createSpotLights();
    void createDirectionalLights();

    RenderedObject* createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition);
    RenderedObject* createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::string path);
    RenderedObject* createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, const std::vector<std::string>& paths);

    u_long createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition);
    u_long createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::string path);
    u_long createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition, const std::vector<std::string>& paths);

    glm::vec4 pickColor();

    __attribute__((unused)) glm::vec4 pickColor(int index);
};

