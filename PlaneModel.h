#pragma once
#include "Models.h"

class PlaneModel : public Models
{
public:
	PlaneModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

