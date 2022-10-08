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

void Application::createNewObject(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject, pair<int, int> indexArray, pair<int, int> vertexCount,
                                  pair<GLsizei, GLsizei> vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition)
{
    this->scene->createAndAdd(countVBOobject, points, sizeOfPoints, countVAOobject, indexArray, vertexCount,
                              vertexOffset, pointer, vertexDefinition, fragmentDefinition);
}

void Application::run()
{
    this->scene->run();
}

