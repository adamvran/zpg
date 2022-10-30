#include "RenderedObject.h"

RenderedObject::RenderedObject()
{
    this->shaderProgram = new ShaderProgram();
    this->transformation = new Transformation();
}

RenderedObject::~RenderedObject() = default;

void RenderedObject::createShader(GLenum shaderType, const char* shaderDefinition)
{
	this->shaderProgram->createShader(shaderType, shaderDefinition);
}

void RenderedObject::initAndCheckShaders()
{
	this->shaderProgram->inicializeShaders();
	this->shaderProgram->checkStatus();
}

void RenderedObject::runShader()
{
	this->shaderProgram->run();
}

void RenderedObject::transformMatrix(float angle, glm::vec3 vector) //rotation
{
	this->transformation->rotation(angle, vector);
}

void RenderedObject::transformMatrix(TransformationType type, glm::vec3 vector) //scale and shift
{
	switch (type)
	{
		case TransformationType::Scale:
			this->transformation->scale(vector);
			break;

		case TransformationType::Shift:
			this->transformation->shift(vector);
			break;
	}
}

void RenderedObject::sendModelMatrixShader()
{
	this->shaderProgram->setMatrixModel(this->transformation->getTransform());
}

void RenderedObject::sendViewMatrixShader(glm::mat4 mat)
{
	this->shaderProgram->setMatrixView(mat);
}

void RenderedObject::sendProjectionMatrixShader(glm::mat4 mat)
{
	this->shaderProgram->setMatrixProjection(mat);
}

ShaderProgram* RenderedObject::getShaderProgram()
{
	return this->shaderProgram;
}

void RenderedObject::createModel(Models* newModel)
{
    this->shape = newModel;
    this->shape->createVBO();
    this->shape->createVAO();
    this->shape->initPositionAndColor();
}

void RenderedObject::drawObjectNEW()
{
    this->shape->drawObject();
}
