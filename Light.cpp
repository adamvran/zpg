//
// Created by Adam Vrána on 29.10.2022.
//

#include "Light.h"

Light::Light()
{
    this->strength = 1;
    this->color = glm::vec4 (0.385, 0.647, 0.812, 1.0);
    this->shiness = 16;
}

Light::Light(glm::vec4 color)
{
    this->strength = 1;
    this->color = color;
    this->shiness = 16;
}

Light::Light(LightType type, glm::vec3 position, glm::vec4 color)
{
    this->strength = 1;
    this->color = color;
    this->shiness = 64;
    this->type = type;
    this->position = position;
    this->direction = glm::vec3(0.0, 0.0, 0.0);

    this->constant = 1;
    this->linear = 0.1;
    this->quadratic = 0.01;
    this->cuttOf = glm::cos(glm::radians(8.5f));
}

Light::~Light() = default;

void Light::updateStrength(float strength) {
    this->strength = strength;
}

void Light::updateColor(glm::vec4 color) {
    this->color = color;
}

void Light::updateShiness(int shiness) {
    this->shiness = shiness;
}

float Light::getConstant() const
{
    return this->constant;
}

float Light::getLinear() const
{
    return this->linear;
}

float Light::getQuadratic() const
{
    return this->quadratic;
}

glm::vec4 Light::getColor()
{
    return this->color;
}

float Light::getStrength() const
{
    return this->strength;
}

int Light::getShiness() const
{
    return this->shiness;
}

LightType Light::getType()
{
    return this->type;
}

__attribute__((unused)) void Light::updateDirection(glm::vec3 direction)
{
    this->direction = direction;
}

__attribute__((unused)) void Light::updatePosition(glm::vec3 position)
{
    this->position = position;
}

__attribute__((unused)) void Light::updateCutOff(float cutOff)
{
    this->cuttOf = cutOff;
}

float Light::getCutOff() const
{
    return this->cuttOf;
}

glm::vec3 Light::getDirection()
{
    return this->direction;
}

glm::vec3 Light::getPosition()
{
    return this->position;
}


