#pragma once
#include "../Models.h"
class PlaneTextureModel : public Models
{
public:
	PlaneTextureModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

