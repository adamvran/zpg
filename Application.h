#pragma once
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
    void createNewObject(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, std::pair<int, int> indexArray, std::pair<int, int> vertexCount,
                         std::pair<GLsizei, GLsizei> vertexOffset, std::pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition);
};


