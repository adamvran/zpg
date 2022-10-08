#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include <cstdio>
#include "ShaderManager.h"
class ShaderProgram
{
private:
    GLuint shaderProgram{};
    ShaderManager* shaderManager;

public:
    ShaderProgram();
    ~ShaderProgram();
    void inicializeShaders();
    void checkStatus() const;
    void run() const;
    void createShader(GLenum shaderType, const char* shaderDefinition);
};

