#pragma once
#include "RenderedObject.h"
#include "Window.h"
#include <vector>
#include "Callback.h"
#include "TransformationType.h"
#include "Camera.h"
#include <algorithm>
#include <iostream>

class Scene
{
private:
	Window* window;
	vector<RenderedObject*> renderedObjects;
	Camera* camera{};

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

	RenderedObject* createRenderedObject(int countVBO, float* points, int sizeOfPoints, int countVAO, pair<int, int> indexArray, int vertexCount,
                                         GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex);
	void addRenderedObject(RenderedObject* obj);
	u_long createAndAdd(int countVBO, float* points, int sizeOfPoints, int countVAO, pair<int, int> indexArray, int vertexCount,
                        GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex);

	void transform(int objectInArray, float angle, glm::vec3 vector);
	void transform(int objectInArray, TransformationType type, glm::vec3 vector);

	void run();

	void createCamera(glm::vec3 eye, glm::vec3 dir);
};

