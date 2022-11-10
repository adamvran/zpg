#pragma once
#include "AbstractTexture.h"
class Texture : public AbstractTexture
{
public:
	Texture();
	Texture(std::vector<std::string> paths, int index);
	void createTexture(int index) override;
};

