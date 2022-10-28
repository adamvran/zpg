#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "ShaderManager.h"
#include <vector>
#include <cstdio>


class Shader
{
private:
	GLuint shaderId{};
	GLenum shaderType;
	const char* shaderDefinition;

public:
	Shader(GLenum shaderType, const char* shaderDefinition);
	void createShader();
	std::vector<GLuint> addShader(std::vector<GLuint> shaders) const; //????
	GLenum getShaderType() const;
};

