#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationType.h"
using namespace std;

class RenderedObject
{
private:
    Model* model{};
    ShaderProgram* shader;
    Transformation* transformation;
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
    void transformMatrix(float angle, glm::vec3 vector);
    void transformMatrix(TransformationType type, glm::vec3 vector);
    void sendMatrixShader();
};

