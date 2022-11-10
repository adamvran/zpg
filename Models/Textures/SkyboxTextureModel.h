#pragma once
#include "../Models.h"

class SkyboxTextureModel : public Models
{
public:
	SkyboxTextureModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

