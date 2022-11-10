#pragma once
#include "../lib/glew/2.2.0_1/include/GL/glew.h"
#include "../lib/glfw/include/GLFW/glfw3.h"
class Models
{
protected:
	GLuint VBO{};
	GLuint VAO{};
	float* points{};
	int sizeOfpoints{};
	int countOfVertex{};
	GLenum objectType{};

public:
	virtual void createVBO() = 0;
	virtual void createVAO() = 0;
	virtual void drawObject() = 0;
	virtual void initPositionAndColor() = 0;
};

