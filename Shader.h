#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "ShaderManager.h"

class Shader
{
private:
    GLuint shaderId{};
    GLenum shaderType;
    const char* shaderDefinition;

public:
    Shader(GLenum shaderType, const char* shaderDefinition);
    void createShader();
    //void addShader(ShaderManager* sh);
    GLuint getShaderId() const;
    GLenum getShaderType() const;
};

