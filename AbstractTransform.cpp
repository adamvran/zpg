#include "AbstractTransform.h"

AbstractTransform::AbstractTransform()
{
	this->matrix = glm::mat4(1.0f);
}

AbstractTransform::~AbstractTransform() = default;

const glm::mat4& AbstractTransform::getTransform() const
{
	return matrix;
}

