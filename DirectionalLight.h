#pragma once
#include "AbstractLight.h"
#include "lib/glm/glm/vec3.hpp"

class DirectionalLight : public AbstractLight
{
private:
	glm::vec3 direction{};

public:
	DirectionalLight(LightType type, glm::vec3 direction, glm::vec4 color);
	void updateStrength(float strength);
	void updateColor(glm::vec4 color);
	void updateShiness(int shiness);
	glm::vec4 getColor();
	float getStrength();
	int getShiness();
	LightType getType();
	void updateDirection(glm::vec3 direction);
	glm::vec3 getDirection();

};

