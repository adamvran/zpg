#include "RenderedObject.h"

RenderedObject::RenderedObject()
{
    this->shader = new ShaderProgram();
}

RenderedObject::~RenderedObject()
{
}

void RenderedObject::createModel(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, pair<int, int> vertexCount,
                                 pair<GLsizei, GLsizei> vertexOffset, pair<GLvoid*, GLvoid*> pointer)
{
    this->model = new Model(sizeOfPoints, points);
    this->model->createVBO(countVBOobject);
    this->model->createVAO(countVAOobject);
    this->initPositionAndColor(indexArray.first, vertexCount.first, vertexOffset.first, pointer.first);
    this->initPositionAndColor(indexArray.second, vertexCount.second, vertexOffset.second, pointer.second);
}

void RenderedObject::initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer)
{
    this->model->initPositionAndColor(indexArray, vertexCount, vertexOffset, pointer);
}

bool RenderedObject::isSet()
{
    return false;
}

void RenderedObject::drawObject(GLenum mode, GLint first, GLsizei count)
{
    this->model->drawObject(mode, first, count);
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
