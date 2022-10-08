#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    ///smazani celeho pole
}

void ShaderManager::addShader(GLuint in_shader, GLenum shaderType)
{
    if (shaderType == GL_VERTEX_SHADER)
        this->vertexArray.push_back(in_shader);
    else if (shaderType == GL_FRAGMENT_SHADER)
        this->fragmentArray.push_back(in_shader);
}

void ShaderManager::createShader(GLenum shaderType, const char* shaderDefinition)
{
    Shader* shader = new Shader(shaderType, shaderDefinition);
    this->addShader(shader->getShaderId(), shaderType);
    //shader->addShader(this);
}

void ShaderManager::initShaders(GLuint shaderProgram)
{
    //vertex
    for (int i = 0; i < this->vertexArray.size(); i++)
    {
        glAttachShader(shaderProgram, this->vertexArray[i]);
    }

    //fragment
    for (int i = 0; i < this->fragmentArray.size(); i++)
    {
        glAttachShader(shaderProgram, this->fragmentArray[i]);
    }
}


