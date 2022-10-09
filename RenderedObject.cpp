#include "RenderedObject.h"
RenderedObject::RenderedObject(){
    this->shader = new ShaderProgram();
    this->transformation = new Transformation();
}
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

void RenderedObject::transformMatrix(float angle, glm::vec3 vector) {
    this->transformation->rotation(angle, vector);
}

void RenderedObject::transformMatrix(TransformationType type, glm::vec3 vector) {
    switch (type) {
        case TransformationType::Scale:
            this->transformation->scale(vector);
            break;
        case TransformationType::Shift:
            this->transformation->shift(vector);
            break;
        default:
            printf("use another method");
            break;
    }
}

void RenderedObject::sendMatrixShader() {
    this->shader->setMatrix(this->transformation->getTransform());
}
