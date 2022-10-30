#include "SphereModel.h"

SphereModel::SphereModel()
{
	this->points = const_cast<float*> (sphere);
	this->sizeOfpoints = sizeof(sphere);
	this->countOfVertex = 2880;
	this->objectType = GL_TRIANGLES;
}

void SphereModel::createVBO()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void SphereModel::createVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void SphereModel::drawObject()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void SphereModel::initPositionAndColor()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
