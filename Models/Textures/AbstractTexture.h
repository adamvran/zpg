#pragma once
#include <string>
#include "../../lib/glew/2.2.0_1/include/GL/glew.h"
#include <iostream>
#include <vector>

class AbstractTexture
{
protected:
	GLuint textureID;
	std::vector<std::string> paths;
public:
	AbstractTexture();
	virtual void createTexture(int index) = 0;
	GLuint getTexture() const;
};

