#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->shaderManager = new ShaderManager();
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::inicializeShaders()
{
    this->shaderProgram = glCreateProgram();
    this->shaderManager->initShaders(this->shaderProgram);
    glLinkProgram(this->shaderProgram);
}

void ShaderProgram::checkStatus()
{
    GLint status;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

}

void ShaderProgram::createShader(GLenum shaderType, const char* shaderDefinition)
{
    this->shaderManager->createShader(shaderType, shaderDefinition);
}

void ShaderProgram::run()
{
    glUseProgram(this->shaderProgram);
}