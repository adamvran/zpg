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
    void
    createNewObject(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                    int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer,
                    const char *vertexDefinition, const char *fragmentDefinition);
};


