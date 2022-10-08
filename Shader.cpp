#include "Shader.h"


Shader::Shader(GLenum shaderType, const char* shaderDefinition)
{
    this->shaderType = shaderType;
    this->shaderDefinition = shaderDefinition;

    this->createShader();
}

void Shader::createShader()
{
    this->shaderId = glCreateShader(this->shaderType);
    glShaderSource(this->shaderId, 1, &this->shaderDefinition, nullptr);
    glCompileShader(this->shaderId);
}


/*void Shader::addShader(ShaderManager* sh)
{
	//sh->addShader(this->shaderId, this->shaderType);
}*/

GLuint Shader::getShaderId() const
{
    return this->shaderId;
}

GLenum Shader::getShaderType() const
{
    return this->shaderType;
}
