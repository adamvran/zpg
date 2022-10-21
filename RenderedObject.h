#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationType.h"


using namespace std;

class RenderedObject
{
private:
	Model* model{};
	ShaderProgram* shaderProgram;
	Transformation* transformation;
	GLenum objectType;
	int countVertex;

public:
	//create object
	RenderedObject(GLenum objectType, int countVertex);
	~RenderedObject();
	void createModel(int countVBO, float* points, int sizeOfPoints, int countVAO,
                     pair<int, int> indexArray, int vertexCount, GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer);

	//object stuff
	void drawObject();
	void initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer);

	//shader stuff
	void createShader(GLenum shaderType, const char* shaderDefinition);
	void initAndCheckShaders();
	void runShader();

	//transformations
	void transformMatrix(float angle, glm::vec3 vector);
	void transformMatrix(TransformationType type, glm::vec3 vector);

	//sending matrices
	void sendModelMatrixShader();
	void sendViewMatrixShader(glm::mat4 mat);
	void sendProjectionMatrixShader(glm::mat4 mat);

	//getters
	ShaderProgram* getShaderProgram();
};

