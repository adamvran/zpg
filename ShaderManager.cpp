#include "ShaderManager.h"

ShaderManager::ShaderManager()= default;
ShaderManager::~ShaderManager()= default;

void ShaderManager::addShader(GLuint in_shader, GLenum shaderType)
{
    if (shaderType == GL_VERTEX_SHADER)
        this->vertexArray.push_back(in_shader);
    else if (shaderType == GL_FRAGMENT_SHADER)
        this->fragmentArray.push_back(in_shader);
}

void ShaderManager::createShader(GLenum shaderType, const char* shaderDefinition)
{
    auto* shader = new Shader(shaderType, shaderDefinition);
    this->addShader(shader->getShaderId(), shaderType);
    //shader->addShader(this);
}

void ShaderManager::initShaders(GLuint shaderProgram)
{
    for (auto i : this->vertexArray)
        glAttachShader(shaderProgram, i);

    for (auto i : this->fragmentArray)
        glAttachShader(shaderProgram, i);
}


