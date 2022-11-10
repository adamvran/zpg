#pragma once
#include "Models.h"

class PlainModel : public Models
{
public:
	PlainModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

