#pragma once

#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "MatrixType.h"

class Observer {

public:
    virtual void notify(MatrixType type, glm::mat4 matrix) = 0;
    virtual void notify(MatrixType type) = 0;
};
