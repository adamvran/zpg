#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include <cstdio>

class ShaderManager
{
private:
    GLint shader_program{};
    GLuint* shader_arr;
    int count_shaders;

public:
    ShaderManager();
    ~ShaderManager();
    void initShaders();
    void addShader(GLuint id_shader);
    void checkStatus() const;
    void init() const;
};

