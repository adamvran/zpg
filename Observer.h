#pragma once

#include "lib/glm/glm/ext/matrix_float4x4.hpp"
#include "MatrixType.h"

class Observer {

public:
    virtual void notify(MatrixType matrixType, glm::mat4 mat) = 0;
};
