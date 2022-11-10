#pragma once
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationType.h"
#include "Models.h"
#include "AbstractTransform.h"


class RenderedObject
{
private:
    Models* shape{};
    ShaderProgram* shaderProgram;

	Transformation* transformation;
    __attribute__((unused)) AbstractTransform* abstractTransform;
    __attribute__((unused)) GLenum objectType{};
    __attribute__((unused)) int countVertex{};

public:
    RenderedObject();
    ~RenderedObject();

	void createShader(GLenum shaderType, const char* shaderDefinition);
	void initAndCheckShaders();
	void runShader();

	void transformMatrix(float angle, glm::vec3 vector);
	void transformMatrix(TransformationType type, glm::vec3 vector);

	void sendModelMatrixShader();
	void sendViewMatrixShader(glm::mat4 mat);
	void sendProjectionMatrixShader(glm::mat4 mat);

	//getters
	ShaderProgram* getShaderProgram();

    void createModel(Models* newModel);
    void drawObject();

    //nastaven� camery pro shaderProgram
    void setCamera(Camera* c);

    void updateLights(std::vector<Light*> lights);
    void updatePointLights(std::vector<PointLight*> lights);
    void updateSpotLights(std::vector<SpotLight*> lights);
    void updateDirLights(std::vector<DirectionalLight*> lights);

};

