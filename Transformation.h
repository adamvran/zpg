#pragma once
#include "lib/glm/glm/detail/type_mat4x4.hpp"
#include <vector>
#include <cstdio>

class Transformation
{
private:
	glm::mat4 transform{};
public:
	Transformation();
	~Transformation();
	void rotation(float angle, glm::vec3 vector);
	void scale(glm::vec3 vector);
	void shift(glm::vec3 vector);
	const glm::mat4 &getTransform() const;
};

