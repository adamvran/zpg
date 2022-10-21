#include "RenderedObject.h"

RenderedObject::RenderedObject(GLenum objectType, int countVertex)
{
	this->shaderProgram = new ShaderProgram();
	this->transformation = new Transformation();
	this->objectType = objectType;
	this->countVertex = countVertex;
}

RenderedObject::~RenderedObject() = default;

void RenderedObject::createModel(int countVBO, float* points, int sizeOfPoints, int countVAO,
                                 pair<int, int> indexArray, int vertexCount, GLsizei vertexOffset,
                                 pair<GLvoid*, GLvoid*> pointer)
{
	this->model = new Model(sizeOfPoints, points);
	this->model->createVBO(countVBO);
	this->model->createVAO(countVAO);
	this->initPositionAndColor(indexArray.first, vertexCount, vertexOffset, pointer.first);
	this->initPositionAndColor(indexArray.second, vertexCount, vertexOffset, pointer.second);
}

void RenderedObject::drawObject()
{
	this->model->drawObject(this->objectType, 0, this->countVertex);
}

void RenderedObject::initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer)
{
	this->model->initPositionAndColor(indexArray, vertexCount, vertexOffset, pointer);
}

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

void RenderedObject::transformMatrix(float angle, glm::vec3 vector)
{
	this->transformation->rotation(angle, vector);
}

void RenderedObject::transformMatrix(TransformationType type, glm::vec3 vector)
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

