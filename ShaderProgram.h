#pragma once
#include <stdio.h>
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "ShaderManager.h"


class Camera;
class ShaderProgram
{
private:
	GLuint shaderProgram;
	ShaderManager* shaderManager;

public:
	ShaderProgram();
	~ShaderProgram();
	void inicializeShaders();
	void checkStatus();
	void run();
	void createShader(GLenum shaderType, const char* shaderDefinition);
	void setMatrixModel(glm::mat4 mat);
	void notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void setMatrixView(glm::mat4 mat);
	void setMatrixProjection(glm::mat4 mat);
};

