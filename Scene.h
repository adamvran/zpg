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
	Camera* camera;

public:
	Scene(int width, int height, const char* title); ///KONSTRUKTOR SC�NY
	~Scene();

	///INICIALIZACE KNIHOVEN A SPR�VA OKNA
	static void initGLFW();
	static void initGLEW();
    static void initOpenGLVersion();
    void initMouse();
	void printVersionInfo();
	int isWindowClosed();
	void drawOntoWindow();

	//VYTVO�EN� A P�ID�N� NOV�HO OBJEKTU
	RenderedObject* createRenderedObject(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, int vertexCount,
		GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex);
	void addRenderedObject(RenderedObject* obj);
	int createAndAdd(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, int vertexCount,
		GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex);

	//TRASFORMACE OBJEKTU
	void transform(int objectInArray, float angle, glm::vec3 vector);
	void transform(int objectInArray, TransformationType type, glm::vec3 vector);

	///SMY�KA WHILE
	void run();

	///SRANDY OHLEDN� KAMERY
	void createCamera(glm::vec3 eye, glm::vec3 dir);
};

