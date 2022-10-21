#include "ShaderManager.h"

ShaderManager::ShaderManager() = default;

ShaderManager::~ShaderManager() = default;


void ShaderManager::createShader(GLenum shaderType, const char* shaderDefinition)
{
    auto* shader = new Shader(shaderType, shaderDefinition);
    if (shaderType == GL_VERTEX_SHADER)
        this->vertexArray = shader->addShader(this->vertexArray);

    else if (shaderType == GL_FRAGMENT_SHADER)
        this->fragmentArray = shader->addShader(this->fragmentArray);

}

void ShaderManager::initShaders(GLuint shaderProgram)
{
    for (auto vertex : this->vertexArray)
        glAttachShader(shaderProgram, vertex);

    for (auto fragment : this->fragmentArray)
        glAttachShader(shaderProgram, fragment);
}


