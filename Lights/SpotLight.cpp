#include "SpotLight.h"

SpotLight::SpotLight(LightType type, glm::vec3 direction, glm::vec4 color, float cutOff)
{
    this->type = type;
    this->direction = direction;
    this->position = glm::vec3(0.0, 0.0, 0.0);
    this->cuttOff = cutOff;
    this->strength = 0.5;
    this->shiness = 64;
    this->color = color;

    this->constant = 1;
    this->linear = 0.1;
    this->quadratic = 0.01;
}

void SpotLight::updateStrength(float strength)
{
    this->strength = strength;
}

void SpotLight::updateColor(glm::vec4 color)
{
    this->color = color;
}

void SpotLight::updateShiness(int shiness)
{
    this->shiness = shiness;
}

float SpotLight::getConstant() const
{
    return this->constant;
}

float SpotLight::getLinear() const
{
    return this->linear;
}

float SpotLight::getQuadratic() const
{
    return this->quadratic;
}

glm::vec4 SpotLight::getColor()
{
    return this->color;
}

float SpotLight::getStrength()
{
    return this->strength;
}

int SpotLight::getShiness()
{
    return this->shiness;
}

LightType SpotLight::getType()
{
    return this->type;
}

void SpotLight::updateDirection(glm::vec3 direction_)
{
    this->direction = direction_;
}

__attribute__((unused)) void SpotLight::updatePosition(glm::vec3 position_)
{
    this->position = position_;
}

__attribute__((unused)) void SpotLight::updateCutOff(float cutOff)
{
    this->cuttOff = cutOff;
}

float SpotLight::getCutOff() const
{
    return this->cuttOff;
}

glm::vec3 SpotLight::getDirection()
{
    return this->direction;
}

glm::vec3 SpotLight::getPosition()
{
    return this->position;
}
