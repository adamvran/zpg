#pragma once
#include <vector>
#include <cstdio>
#include "lib/glm/glm/ext/matrix_float4x4.hpp"

class AbstractTransform
{
protected:
	glm::mat4 matrix{};
public:
	AbstractTransform();
	~AbstractTransform();
	const glm::mat4& getTransform() const;
};

