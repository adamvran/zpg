#pragma once
#include <cstdio>
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "ShaderManager.h"
#include "Observer.h"
#include "Camera.h"
#include "Observer.h"
#include "MatrixType.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"


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
	void setMatrixModel(glm::mat4 mat) const;
    void notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void notify(Camera* camera);
    void notify(MatrixType type, glm::mat4 matrix);
    void notify(MatrixType type);
    void setMatrixView(glm::mat4 mat) const;
	void setMatrixProjection(glm::mat4 mat) const;

    __attribute__((unused)) void setStrength(float strength) const;
    __attribute__((unused)) void setColor(glm::vec4 color) const;
    void setShiness(int shiness) const;
    void setActiveCamera(Camera* camera);

    //update light
    void setActualLight(GLint count) const;
    void updateLights(std::vector<Light*> lights) const;


    //
    void updatePointLights(std::vector<PointLight*> lights) const;
    void updateSpotLights(std::vector<SpotLight*> lights) const;
    void updateDirLights(std::vector<DirectionalLight*> lights) const;

};

