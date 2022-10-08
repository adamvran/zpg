#include "RenderedObject.h"

RenderedObject::RenderedObject(){ this->shader = new ShaderProgram(); }
RenderedObject::~RenderedObject() = default;

void RenderedObject::createModel(int countVBOObject, float* points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray, int vertexCount,
                                 GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer)
{
    this->model = new Model(sizeOfPoints, points);
    this->model->createVBO(countVBOObject);
    this->model->createVAO(countVAOObject);
    RenderedObject::initPositionAndColor(indexArray.first, vertexCount, vertexOffset, pointer.first);
    RenderedObject::initPositionAndColor(indexArray.second, vertexCount, vertexOffset, pointer.second);
}

void RenderedObject::initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer)
{
    Model::initPositionAndColor(indexArray, vertexCount, vertexOffset, pointer);
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
