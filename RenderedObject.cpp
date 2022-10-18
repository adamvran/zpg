#include "RenderedObject.h"

RenderedObject::RenderedObject(GLenum objectType, int countVertex)
{
	this->shader = new ShaderProgram();
	this->transformation = new Transformation();
	this->objectType = objectType;
	this->countVertex = countVertex;
}

RenderedObject::~RenderedObject()
{
}

void RenderedObject::createModel(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, 
	pair<int, int> indexArray, int vertexCount, GLsizei vertexOffset, 
	pair<GLvoid*, GLvoid*> pointer)
{
	this->model = new Model(sizeOfPoints, points);
	this->model->createVBO(countVBOobject);
	this->model->createVAO(countVAOobject);
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
	this->shader->createShader(shaderType, shaderDefinition);
}

void RenderedObject::initAndCheckShaders()
{
	this->shader->inicializeShaders();
	this->shader->checkStatus();
}

void RenderedObject::runShader()
{
	this->shader->run();
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
	this->shader->setMatrixModel(this->transformation->getTransform());
}

void RenderedObject::sendViewMatrixShader(glm::mat4 mat)
{
	this->shader->setMatrixView(mat);
}

void RenderedObject::sendProjectionMatrixShader(glm::mat4 mat)
{
	this->shader->setMatrixProjection(mat);
}

ShaderProgram* RenderedObject::getShaderProgram()
{
	return this->shader;
}

