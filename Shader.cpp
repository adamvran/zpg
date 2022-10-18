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
	glShaderSource(this->shaderId, 1, &this->shaderDefinition, NULL);
	glCompileShader(this->shaderId);
}

std::vector<GLuint> Shader::addShader(std::vector<GLuint> shaders)
{
	 shaders.push_back(this->shaderId);
	 return shaders;
}

GLenum Shader::getShaderType()
{
	return this->shaderType;
}
