#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "Model.h"
#include "ShaderProgram.h"

using namespace std;

class RenderedObject
{
private:
    Model* model{};
    ShaderProgram* shader;

public:
    RenderedObject();
    void createModel(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                     int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer);
    ~RenderedObject();
    void drawObject(GLenum mode, GLint first, GLsizei count);
    static void initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer);
    void createShader(GLenum shaderType, const char* shaderDefinition);
    void initAndCheckShaders();
    void runShader();

};

