#include "Transformation.h"
#include "lib/glm/glm/ext/matrix_transform.hpp"

Transformation::Transformation()
{
	this->transorm = glm::mat4(1.0f);
}

Transformation::~Transformation()
{
}

/*void Transformation::addTransformation(Transformation* t)
{
	this->transformations.push_back(t);
}*/

void Transformation::rotation(float angle, glm::vec3 vector)
{
	this->transorm = glm::rotate(this->transorm, angle, vector);
}

void Transformation::scale(glm::vec3 vector)
{
	this->transorm = glm::scale(this->transorm, vector);
}

void Transformation::shift(glm::vec3 vecotr)
{
	this->transorm = glm::translate(this->transorm, vecotr);
}

const glm::mat4 &Transformation::getTransform() const
{
	return transorm;
}

/*std::vector<Transformation*> Transformation::getTransformations()
{
	return this->transformations;
}*/
