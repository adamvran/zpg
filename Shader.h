#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "ShaderManager.h"
class Shader {
private:
    GLuint id_shader{};
    GLenum type_shader;
    const char* shader;

public:
    Shader(GLenum type_shader, const char* shader);
    ~Shader();
    void createShader(ShaderManager* manager);
};