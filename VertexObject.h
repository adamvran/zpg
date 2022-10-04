#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
class VertexObject
{
private:
    GLuint VBO;
    GLuint VAO;
    float *points;
    int size_points;
    //Model *model a v modelu bude VAO a VBO
public:
    VertexObject(float *points, int size_points);
    ~VertexObject();
    void createVBO(int count);
    void createVAO(int count, int enable_vertex_att_arr, int index, int size, GLsizei stride, const GLvoid* pointer);
    void drawVertexObject() const;
};

