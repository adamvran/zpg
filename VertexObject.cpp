#include "VertexObject.h"

VertexObject::VertexObject(float *points, int size_points) {
    this->VBO = 0;
    this->VAO = 0;
    this->points = points;
    this->size_points = size_points;
}

VertexObject::~VertexObject() = default;

void VertexObject::createVBO(int count) {
    glGenBuffers(count, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->size_points, this->points, GL_STATIC_DRAW);
}

void VertexObject::createVAO(int count, int enable_vertex_att_arr, int index, int size, GLsizei	stride, const GLvoid* pointer) {
    glGenVertexArrays(count, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(enable_vertex_att_arr);

}

void VertexObject::drawVertexObject() const {
    glBindVertexArray(this->VAO);
}
