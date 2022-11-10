#pragma once
#include "../lib/glm/glm/vec4.hpp"
#include "LightType.h"
class AbstractLight
{
protected:
	float strength;
	glm::vec4 color{};
	int shiness;
	LightType type;

public:
	AbstractLight();
	virtual glm::vec4 getColor() = 0;
	virtual float getStrength() = 0;
	virtual int getShiness() = 0;
	virtual LightType getType() = 0;

    __attribute__((unused)) virtual void updateStrength(float strength) = 0;

    __attribute__((unused)) virtual void updateColor(glm::vec4 color) = 0;

    __attribute__((unused)) virtual void updateShiness(int shiness) = 0;

};

