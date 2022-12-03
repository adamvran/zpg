#pragma once
#include "AbstractLight.h"
#include "../lib/glm/glm/vec3.hpp"
class PointLight : public AbstractLight
{
private:
	glm::vec3 position{};
	LightType type;

	//utlum
	float constant;
	float linear;
	float quadratic;

public:
	PointLight(LightType type, glm::vec3 position, glm::vec4 color);
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

    __attribute__((unused)) void updatePosition(glm::vec3 position_);
	glm::vec3 getPosition();
};

