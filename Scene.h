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
    static void printVersionInfo();
    int isWindowClosed();
    void drawOntoWindow();
    static RenderedObject* createRenderedObject(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                                                int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer, const char *vertexDefinition,
                                                const char *fragmentDefinition);
    void
    createAndAdd(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                 int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer, const char *vertexDefinition,
                 const char *fragmentDefinition);
    void addRenderedObject(RenderedObject* obj);
    void run();


};

