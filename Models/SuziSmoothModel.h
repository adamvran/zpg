#pragma once
#include "Models.h"
#include "suzi_smooth.h"

class SuziSmoothModel : public Models
{
public:
	SuziSmoothModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

