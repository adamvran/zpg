#pragma once
#include <cstdio>
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "ShaderManager.h"
#include "Observer.h"


class Camera;
class ShaderProgram : public Observer
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
	void notify(MatrixType matrixType, glm::mat4 matrix) override;
	void setMatrixView(glm::mat4 mat) const;
	void setMatrixProjection(glm::mat4 mat) const;
    void setStrength(float strength) const;
    void setColor(glm::vec4 color) const;
    void setShiness(int shiness) const;
};

