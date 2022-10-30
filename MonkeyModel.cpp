#include "MonkeyModel.h"

MonkeyModel::MonkeyModel()
{
	this->points = const_cast<float*> (suziSmooth);
	this->sizeOfpoints = sizeof(suziSmooth);
	this->countOfVertex = 2904;
	this->objectType = GL_TRIANGLES;
}

void MonkeyModel::createVBO()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void MonkeyModel::createVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void MonkeyModel::drawObject()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void MonkeyModel::initPositionAndColor()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
