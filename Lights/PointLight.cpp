#include "PointLight.h"

PointLight::PointLight(LightType type, glm::vec3 position, glm::vec4 color)
{
	this->strength = 1;
	this->color = color;
	this->shiness = 128;
	this->type = type;
	this->position = position;

	this->constant = 1;
	this->linear = 0.1;
	this->quadratic = 0.01;
}

void PointLight::updateStrength(float strength)
{
	this->strength = strength;
}

void PointLight::updateColor(glm::vec4 color)
{
	this->color = color;
}

void PointLight::updateShiness(int shiness)
{
	this->shiness = shiness;
}

float PointLight::getConstant() const
{
    return this->constant;
}

float PointLight::getLinear() const
{
    return this->linear;
}

float PointLight::getQuadratic() const
{
	return this->quadratic;
}

glm::vec4 PointLight::getColor()
{
    return this->color;
}

float PointLight::getStrength()
{
    return this->strength;
}

int PointLight::getShiness()
{
    return this->shiness;
}

LightType PointLight::getType()
{
    return this->type;
}

__attribute__((unused)) void PointLight::updatePosition(glm::vec3 position_)
{
	this->position = position_;
}

glm::vec3 PointLight::getPosition()
{
    return this->position;
}
