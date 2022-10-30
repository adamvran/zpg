#include "TreeModel.h"

TreeModel::TreeModel()
{
	this->points = const_cast<float*> (tree);
	this->sizeOfpoints = sizeof(tree);
	this->countOfVertex = 92814;
	this->objectType = GL_TRIANGLES;
}

void TreeModel::createVBO()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void TreeModel::createVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void TreeModel::drawObject()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void TreeModel::initPositionAndColor()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
