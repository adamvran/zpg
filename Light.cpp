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

Light::~Light() = default;

void Light::updateStrength(int strength) {
    this->strength = strength;
}

void Light::updateColor(glm::vec4 color) {
    this->color = color;
}

void Light::updateShiness(int shiness) {
    this->shiness = shiness;
}

void Light::update() {

}

