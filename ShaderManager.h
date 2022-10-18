#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Shader.h"

using namespace std;

class ShaderManager
{
private:
	vector<GLuint> vertexArray;
	vector<GLuint> fragmentArray;;


public:
	ShaderManager();
	~ShaderManager();
	void initShaders(GLuint shaderProgram);
	void createShader(GLenum shaderType, const char* shaderDefinition);
};

