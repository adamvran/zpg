#pragma once
#include "AbstractLight.h"
#include "../lib/glm/glm/vec3.hpp"

class DirectionalLight : public AbstractLight
{
private:
	glm::vec3 direction{};

public:
	DirectionalLight(LightType type, glm::vec3 direction, glm::vec4 color);
	void updateStrength(float strength) override;
	void updateColor(glm::vec4 color) override;
	void updateShiness(int shiness) override;
	glm::vec4 getColor() override;
	float getStrength() override;
	int getShiness() override;
	LightType getType() override;

    __attribute__((unused)) void updateDirection(glm::vec3 direction_);
	glm::vec3 getDirection();

};

