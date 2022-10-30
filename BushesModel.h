#pragma once
#include "Models.h"

class BushesModel : public Models
{
public:
	BushesModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

