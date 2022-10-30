#pragma once
#include "Models.h"
#include "Models/suzi_smooth.h"

class MonkeyModel : public Models
{
public:
	MonkeyModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

