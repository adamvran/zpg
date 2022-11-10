#include <iostream>
#include "ShaderManager.h"

ShaderManager::ShaderManager() = default;

ShaderManager::~ShaderManager() = default;


void ShaderManager::createShader(GLenum shaderType, const char* shaderDefinition)
{
    auto* shader = new Shader(shaderType, shaderDefinition);
    switch (shaderType) {
        case GL_VERTEX_SHADER:
            this->vertexArray = shader->addShader(this->vertexArray);
            break;

        case GL_FRAGMENT_SHADER:
            this->fragmentArray = shader->addShader(this->fragmentArray);
            break;

        default:
            std::cout << "Something wrong" << std::endl;
    }
}

void ShaderManager::initShaders(GLuint shaderProgram)
{
    for (auto vertex : this->vertexArray)
        glAttachShader(shaderProgram, vertex);

    for (auto fragment : this->fragmentArray)
        glAttachShader(shaderProgram, fragment);
}
