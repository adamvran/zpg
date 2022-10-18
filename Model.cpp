#include "Model.h"
Model::Model(int sizeOfpoints, float* points)
{
	this->VBO = 0;
	this->VAO = 0;
	this->sizeOfpoints = sizeOfpoints;
	this->points = points;
}

Model::~Model()
{
}

void Model::createVBO(int countObject)
{
	glGenBuffers(countObject, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void Model::createVAO(int countObject)
{
	glGenVertexArrays(countObject, &this->VAO);
	glBindVertexArray(this->VAO);
	/*glEnableVertexAttribArray(enableVertesAttribArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(indexArray, vertexCount, GL_FLOAT, GL_FALSE, vertexOffset, NULL);*/
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Model::initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer)
{
	glVertexAttribPointer(indexArray, vertexCount, GL_FLOAT, GL_FALSE, vertexOffset, pointer);
	glEnableVertexAttribArray(indexArray);
}

void Model::drawObject(GLenum mode, GLint first, GLsizei count)
{
	glBindVertexArray(this->VAO);
	glDrawArrays(mode, first, count);
}
