#include "PlaneTextureModel.h"
#include "triangle.h"

PlaneTextureModel::PlaneTextureModel()
{
	this->points = const_cast<float*> (triangle);
	this->sizeOfpoints = sizeof(triangle);
	this->countOfVertex = 8;
	this->objectType = GL_TRIANGLES;
}

void PlaneTextureModel::createVBO()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void PlaneTextureModel::createVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void PlaneTextureModel::drawObject()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void PlaneTextureModel::initPositionAndColor()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
