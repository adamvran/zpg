#pragma once
#include "../AbstractTexture.h"
class Skybox : public AbstractTexture
{
public:
	Skybox();
	Skybox(std::vector<std::string> paths, int index);
	void createTexture(int index) override;
};

