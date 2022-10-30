#pragma once
#include "Models/tree.h"
#include "Models.h"

class TreeModel : public Models
{
public:
	TreeModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

