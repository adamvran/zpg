#pragma once
#include "Models.h"
#include "gift.h"

class GiftModel : public Models
{
public:
	GiftModel();
	void createVBO() override;
	void createVAO() override;
	void drawObject() override;
	void initPositionAndColor() override;
};

