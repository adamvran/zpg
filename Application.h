#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "Scene.h"

class Application
{
private:
	Scene* scene;

public:
	Application(int width, int height, const char* title);
	~Application();
	void createScene(int width, int height, const char* title);
	void run();

	int createNewObject(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, int vertexCount,
		GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex);

	void transformObject(int objectInArray, float angle, glm::vec3 vector);
	void transformObject(int objectInArray, TransformationType type, glm::vec3 vector);

	///kamera srandy
	void createCamera(glm::vec3 eye, glm::vec3 dir);
};


