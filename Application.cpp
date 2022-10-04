#include "Application.h"
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"


Application::Application(int width, int height) {
    glfwSetErrorCallback(Callback::errorCallback);
    Application::initGLFW();
    Application::initOpenGLVersion();
    this->window = new Window(width, height);
    Application::initGLEW();
    Application::printVersionInfo();
    this->window->windowSize();

    //create shader manager
    this->shader_manager = new ShaderManager();
}

Application::~Application() {
    this->window->~Window();
    glfwTerminate();
}

void Application::initGLFW() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    glewInit();
}

void Application::printVersionInfo() {
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::createVertexObject(int count_vbo, int count_vao, int size, int index, float *points,
                                     int enable_vertex_att_arr, int size_points, GLsizei stride, const GLvoid* pointer){
    this->vertex_object = new VertexObject(points, size_points);
    this->vertex_object->createVBO(count_vbo);
    this->vertex_object->createVAO(count_vao, enable_vertex_att_arr, index, size, stride, pointer);
}

void Application::createShader(GLenum type_shader, const char* shader1) {
    this->shader = new Shader(type_shader, shader1);
    this->shader->createShader(shader_manager);
}

void Application::initOpenGLVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::run() {
    this->shader_manager->initShaders();
    this->shader_manager->checkStatus();
    loop();
}

void Application::loop() {
    while (!this->window->windowClosed()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->shader_manager->init();
        this->vertex_object->drawVertexObject();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        this->window->renderWindow();
    }
}
