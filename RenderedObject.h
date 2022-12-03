#pragma once
#include "ShaderControll/ShaderProgram.h"
#include "Transformations/Transformation.h"
#include "Transformations/TransformationType.h"
#include "Models/Models.h"
#include "Transformations/AbstractTransform.h"
#include "Models/Textures/Texture.h"
#include "Models/Textures/AbstractTexture.h"
#include "Skybox.h"


class RenderedObject
{
private:
    Models* shape{};
    ShaderProgram* shaderProgram;

	Transformation* transformation;
    __attribute__((unused)) AbstractTransform* abstractTransform;
    __attribute__((unused)) GLenum objectType{};
    __attribute__((unused)) int countVertex{};
    AbstractTexture* texture;


public:
    RenderedObject();
    ~RenderedObject();

	void createShader(GLenum shaderType, const char* shaderDefinition);
	void initAndCheckShaders();
	void runShader();

	void transformMatrix(float angle, glm::vec3 vector);
	void transformMatrix(TransformationType type, glm::vec3 vector);

	void sendModelMatrixShader();
	void sendSkyboxViewMatrix(glm::mat4 mat);
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

    //textury
    GLuint getTexture();

    void useTexture();


    //abstraktn� textura
    AbstractTexture* getTextureObject();
    void createTexture(const std::vector<std::string>& paths, int index);
    void useTexture2();

};

