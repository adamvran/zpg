#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    
}

ShaderManager::~ShaderManager()
{
    ///smazani celeho pole
}


void ShaderManager::createShader(GLenum shaderType, const char* shaderDefinition)
{
    Shader* shader = new Shader(shaderType, shaderDefinition);
    if (shaderType == GL_VERTEX_SHADER)
        this->vertexArray = shader->addShader(this->vertexArray);
    else if (shaderType == GL_FRAGMENT_SHADER)
        this->fragmentArray = shader->addShader(this->fragmentArray);
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


