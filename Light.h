#pragma once

#include "lib/glm/glm/vec4.hpp"

class Light {
private:
    int strength;
    glm::vec4 color{};
    int shiness;
public:
    Light();
    ~Light();
    void updateStrength(int strength);
    void updateColor(glm::vec4 color);
    void updateShiness(int shiness);
    void update();

};
