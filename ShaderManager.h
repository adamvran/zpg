#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Shader.h"

using namespace std;

class ShaderManager
{
private:
    vector<GLuint> vertexArray;
    vector<GLuint> fragmentArray;;


public:
    ShaderManager();
    ~ShaderManager();
    void addShader(GLuint in_shader, GLenum shaderType);
    void initShaders(GLuint shaderProgram);
    void createShader(GLenum shaderType, const char* shaderDefinition);
};

