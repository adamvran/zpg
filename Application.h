#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "Window.h"
#include "Callback.h"
#include "VertexObject.h"
#include "Shader.h"
#include "ShaderManager.h"
#include <cstdlib>
#include <cstdio>
class Application {
private:
    Window* window;
    VertexObject* vertex_object{};
    Shader* shader{};
    ShaderManager* shader_manager{};
public:
    Application(int width, int height);
    ~Application();
    static void initGLFW();
    static void initGLEW();
    static void initOpenGLVersion();
    static void printVersionInfo();

    void createVertexObject(int count_vbo, int count_vao, int size, int index, float *points,
                            int enable_vertex_att_arr, int size_points, GLsizei	stride, const GLvoid* pointer);
    void createShader(GLenum type_shader, const char* shader1);
    void loop();
    void run();
};
