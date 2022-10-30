#pragma once

#include "lib/glm/glm/vec4.hpp"
#include "ShaderProgram.h"

class Light {
private:
    float strength;
    glm::vec4 color{};
    int shiness;

public:
    Light();
    Light(glm::vec4 color);
    ~Light();
    void updateStrength(int strength);
    void updateColor(glm::vec4 color);
    void updateShiness(int shiness);
    void update(ShaderProgram* sh);

};
