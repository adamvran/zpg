#include "Application.h"

Application::Application(int width, int height, const char* title)
{
    this->createScene(width, height, title);
}

Application::~Application()
{
    this->scene->~Scene();
}

void Application::createScene(int width, int height, const char* title)
{
    this->scene = new Scene(width, height, title);
}

void Application::createNewObject(int countVBOObject, float* points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray, int vertexCount,
                                  GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition)
{
    this->scene->createAndAdd(countVBOObject, points, sizeOfPoints, countVAOObject, indexArray, vertexCount,
                              vertexOffset, pointer, vertexDefinition, fragmentDefinition);
}

void Application::run()
{
    this->scene->run();
}

