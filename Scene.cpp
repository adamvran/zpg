#include "Scene.h"

Scene::Scene(int width, int height, const char* title)
{
    glfwSetErrorCallback(Callback::error_callback);
    Scene::initGLFW();
    Scene::initOpenGLVersion();
    this->window = new Window(width, height, title);
    Scene::initGLEW();
    Scene::printVersionInfo();
    this->window->windowSize();
}

Scene::~Scene()
{
    this->window->~Window();
    glfwTerminate();
}

void Scene::initGLEW()
{
    glewExperimental = GL_TRUE;
    glewInit();
}

void Scene::initGLFW()
{
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
}

void Scene::initOpenGLVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void Scene::printVersionInfo()
{
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

int Scene::isWindowClosed()
{
    return this->window->isWindowClosed();
}

void Scene::drawOntoWindow()
{
    this->window->displayAll();
}

RenderedObject* Scene::createRenderedObject(int countVBOObject, float *points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray,
                                            int vertexCount, GLsizei vertexOffset, pair<GLvoid *, GLvoid *> pointer, const char *vertexDefinition,
                                            const char *fragmentDefinition)
{
    auto* renderedObject = new RenderedObject();
    renderedObject->createModel(countVBOObject, points, sizeOfPoints, countVAOObject, indexArray, vertexCount, vertexOffset, pointer);
    renderedObject->createShader(GL_VERTEX_SHADER, vertexDefinition);
    renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentDefinition);
    return renderedObject;
}

void Scene::addRenderedObject(RenderedObject* obj)
{
    this->renderedObjects.push_back(obj);
}

void Scene::createAndAdd(int countVBOObject, float* points, int sizeOfPoints, int countVAOObject, pair<int, int> indexArray, int vertexCount,
                         GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition)
{
    this->addRenderedObject(this->createRenderedObject(countVBOObject, points, sizeOfPoints, countVAOObject, indexArray, vertexCount,
                                                       vertexOffset, pointer, vertexDefinition, fragmentDefinition));
}

void Scene::run(int vertexes)
{
    for (auto object : this->renderedObjects)
    {
        object->initAndCheckShaders();
    }

    while (!this->isWindowClosed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (auto object : this->renderedObjects)
        {
            object->runShader();
            object->transformMatrix(90, glm::vec3(0.0f, 0.0f, 1.0f));
            object->drawObject(GL_TRIANGLES, 0, vertexes);
        }
        glfwPollEvents();
        this->drawOntoWindow();
    }
}
