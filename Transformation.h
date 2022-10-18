#pragma once
#include "lib/glm/glm/detail/type_mat4x4.hpp"
#include <vector>
#include <stdio.h>

class Transformation
{
private:
	glm::mat4 transorm;
	//std::vector<Transformation*> transformations;
public:
	Transformation();
	~Transformation();
	//void addTransformation(Transformation* t);
	void rotation(float angle, glm::vec3 vector);
	void scale(glm::vec3 vector);
	void shift(glm::vec3 vecotr);
	const glm::mat4 &getTransform() const;
	//std::vector<Transformation*> getTransformations();
};

