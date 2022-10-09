#include "Transformation.h"

Transformation::Transformation() {
    this->transform = glm::mat4(1.0f);
}

Transformation::~Transformation() = default;

void Transformation::rotation(float angle, glm::vec3 vector) {
    this->transform = glm::rotate(this->transform, angle, vector);
}

void Transformation::scale(glm::vec3 vector) {
    this->transform = glm::scale(transform, vector);
}

void Transformation::shift(glm::vec3 vector) {
    this->transform = glm::translate(transform, vector);
}

const glm::mat4 &Transformation::getTransform() const {
    return transform;
}
