#pragma once
#include <cstdio>
#include "../lib/glm/glm/ext/matrix_float4x4.hpp"
#include "ShaderManager.h"
#include "../Observer.h"
#include "../Camera.h"
#include "../Observer.h"
#include "../MatrixType.h"
#include "../Lights/Light.h"
#include "../Lights/PointLight.h"
#include "../Lights/SpotLight.h"
#include "../Lights/DirectionalLight.h"


class Camera;
class Light;
class ShaderProgram : public Observer
{
private:
	GLuint shaderProgram{};
	ShaderManager* shaderManager;
    Camera* activeCamera{};


public:
	ShaderProgram();
	~ShaderProgram();
	void inicializeShaders();
	void checkStatus() const;
	void run() const;
	void createShader(GLenum shaderType, const char* shaderDefinition);
	void setMatrixModel(glm::mat4 mat, const std::string& type) const;
    void notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const;
    void notify(Camera* camera) const;
    void notify(MatrixType type, glm::mat4 matrix) override;
    void notify(MatrixType type) override;
    void setMatrixView(glm::mat4 mat) const;
	void setMatrixProjection(glm::mat4 mat) const;

    __attribute__((unused)) void setStrength(float strength) const;
    __attribute__((unused)) void setColor(glm::vec4 color) const;
    void setShiness(GLuint shiness) const;
    void setActiveCamera(Camera* camera);

    //update light
    void setActualLight(GLuint count) const;
    void updateLights(std::vector<Light*> lights) const;


    //
    void updatePointLights(std::vector<PointLight*> lights) const;
    void updateSpotLights(std::vector<SpotLight*> lights) const;
    void updateDirLights(std::vector<DirectionalLight*> lights) const;

    //textury
    void useTexture() const;

    void setMatrixTransform(glm::mat4 mat1) const;
};

