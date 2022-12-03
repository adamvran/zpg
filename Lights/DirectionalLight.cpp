#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(LightType type, glm::vec3 direction, glm::vec4 color)
{
    this->type = type;
    this->direction = direction;
    this->strength = 1;
    this->shiness = 64;
    this->color = color;
}

void DirectionalLight::updateStrength(float strength)
{
    this->strength = strength;
}

void DirectionalLight::updateColor(glm::vec4 color)
{
    this->color = color;
}

void DirectionalLight::updateShiness(int shiness)
{
    this->shiness = shiness;
}

glm::vec4 DirectionalLight::getColor()
{
    return this->color;
}

float DirectionalLight::getStrength()
{
    return this->strength;
}

int DirectionalLight::getShiness()
{
    return this->shiness;
}

LightType DirectionalLight::getType()
{
    return this->type;
}

__attribute__((unused)) void DirectionalLight::updateDirection(glm::vec3 direction_)
{
    this->direction = direction_;
}

glm::vec3 DirectionalLight::getDirection()
{
    return this->direction;
}
