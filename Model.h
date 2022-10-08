#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
class Model
{
private:
    GLuint VBO;
    GLuint VAO;
    float* points;
    int sizeOfPoints;

public:
    Model(int sizeOfPoints, float* points);
    ~Model();
    void createVBO(int countObject);
    void createVAO(int countObject);
    void drawObject(GLenum mode, GLint first, GLsizei count) const;
    static void initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer);
};

