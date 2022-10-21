#pragma once
#include <cstdio>
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "ShaderManager.h"


class Camera;
class ShaderProgram
{
private:
	GLuint shaderProgram{};
	ShaderManager* shaderManager;

public:
	ShaderProgram();
	~ShaderProgram();
	void inicializeShaders();
	void checkStatus() const;
	void run() const;
	void createShader(GLenum shaderType, const char* shaderDefinition);
	void setMatrixModel(glm::mat4 mat) const;
	void notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const;
	void setMatrixView(glm::mat4 mat) const;
	void setMatrixProjection(glm::mat4 mat) const;
};

