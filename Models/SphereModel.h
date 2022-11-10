#pragma once
#include "Models.h"
#include "sphere.h"

class SphereModel : public Models
{
public:
	SphereModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

