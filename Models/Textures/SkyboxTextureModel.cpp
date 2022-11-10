#include "SkyboxTextureModel.h"
#include "skybox.h"

SkyboxTextureModel::SkyboxTextureModel()
{
	this->points = const_cast<float*> (skycube);
	this->sizeOfpoints = sizeof(skycube);
	this->countOfVertex = 108;
	this->objectType = GL_TRIANGLES;
}

void SkyboxTextureModel::createVBO()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, this->points, GL_STATIC_DRAW);
}

void SkyboxTextureModel::createVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void SkyboxTextureModel::drawObject()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void SkyboxTextureModel::initPositionAndColor()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
	glEnableVertexAttribArray(0);
}
