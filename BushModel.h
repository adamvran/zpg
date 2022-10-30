#pragma once
#include "Models.h"

class BushModel : public Models
{
public:
	BushModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

