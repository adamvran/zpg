#pragma once
#include "AbstractLight.h"
#include "../lib/glm/glm/vec3.hpp"

class SpotLight : public AbstractLight
{
private:
	glm::vec3 direction{};
	glm::vec3 position{};
	float constant;
	float linear;
	float quadratic;
	float cuttOff;

public:
	SpotLight(LightType type, glm::vec3 direction, glm::vec4 color, float cutOff);
	void updateStrength(float strength) override;
	void updateColor(glm::vec4 color) override;
	void updateShiness(int shiness) override;

	float getConstant() const;
	float getLinear() const;
	float getQuadratic() const;
	glm::vec4 getColor() override;
	float getStrength() override;
	int getShiness() override;
	LightType getType() override;

	void updateDirection(glm::vec3 direction_);

    __attribute__((unused)) void updatePosition(glm::vec3 position_);
    __attribute__((unused)) void updateCutOff(float cutOff);
	float getCutOff() const;
	glm::vec3 getDirection();
	glm::vec3 getPosition();
};

