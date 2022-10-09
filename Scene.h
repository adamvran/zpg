#pragma once
#include "RenderedObject.h"
#include "Window.h"
#include <vector>
#include "Callback.h"
#include "TransformationType.h"
#include "lib/glm/glm/vec3.hpp" // glm::vec3

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
    void
    createAndAdd(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                 int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer, const char *vertexDefinition,
                 const char *fragmentDefinition, float angle, glm::vec3 vector);
    void
    createAndAdd(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                 int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer, const char *vertexDefinition,
                 const char *fragmentDefinition, TransformationType type, glm::vec3 vector);
    void addRenderedObject(RenderedObject* obj);
    void run(int vertexes);


};

