#include "Model.h"
Model::Model(int sizeOfPoints, float* points)
{
    this->VBO = 0;
    this->VAO = 0;
    this->sizeOfPoints = sizeOfPoints;
    this->points = points;
}

Model::~Model() = default;

void Model::createVBO(int countObject)
{
    glGenBuffers(countObject, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfPoints, this->points, GL_STATIC_DRAW);
}

void Model::createVAO(int countObject)
{
    glGenVertexArrays(countObject, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Model::initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer)
{
    glVertexAttribPointer(indexArray, vertexCount, GL_FLOAT, GL_FALSE, vertexOffset, pointer);
    glEnableVertexAttribArray(indexArray);
}

void Model::drawObject(GLenum mode, GLint first, GLsizei count) const
{
    glBindVertexArray(this->VAO);
    glDrawArrays(mode, first, count);
}
