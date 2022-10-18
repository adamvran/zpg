#pragma once
#include "lib/glm/glm/vec3.hpp"
#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationType.h"


using namespace std;

class RenderedObject
{
private:
	Model* model;
	ShaderProgram* shader;
	Transformation* transformation;
	GLenum objectType;
	int countVertex;

public:
	//vytvo�en� objektu
	RenderedObject(GLenum objectType, int countVertex);
	~RenderedObject();
	void createModel(int countVBOobject, float* points, int sizeOfPoints, int countVAOobject,
		pair<int, int> indexArray, int vertexCount, GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer); 

	//srandy ohledn� objektu
	void drawObject();
	void initPositionAndColor(int indexArray, int vertexCount, GLsizei vertexOffset, const GLvoid* pointer);

	//haha shader srandy
	void createShader(GLenum shaderType, const char* shaderDefinition);
	void initAndCheckShaders();
	void runShader();

	//transformace
	void transformMatrix(float angle, glm::vec3 vector);
	void transformMatrix(TransformationType type, glm::vec3 vector);

	//odesl�n� matic (modelov�, pohledov� a projek�n�) shaderu
	void sendModelMatrixShader();
	void sendViewMatrixShader(glm::mat4 mat);
	void sendProjectionMatrixShader(glm::mat4 mat);

	//nutn� gettery
	ShaderProgram* getShaderProgram();
};

