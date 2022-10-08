#pragma once
#include "RenderedObject.h"
#include "Window.h"
#include <vector>
#include "Callback.h"
class Scene
{
private:
    Window* window;
    vector<RenderedObject*> renderedObjects;

public:
    Scene(int width, int height, const char* title);
    ~Scene();
    static void initGLFW();
    static void initGLEW();
    static void initOpenGLVersion();
    void printVersionInfo();
    int isWindowClosed();
    void drawOntoWindow();
    RenderedObject* createRenderedObject(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, pair<int, int> vertexCount,
                                         pair<GLsizei, GLsizei> vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition);
    void addRenderedObject(RenderedObject* obj);
    void createAndAdd(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, pair<int, int> vertexCount,
                      pair<GLsizei, GLsizei> vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition);
    void run();
};

