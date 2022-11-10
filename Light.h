#pragma once

#include "lib/glm/glm/vec4.hpp"
#include "ShaderProgram.h"
#include "LightType.h"


class Light {
private:
    float strength;
    glm::vec4 color{};
    int shiness;

    glm::vec3 direction{};
    glm::vec3 position{};
    LightType type;

    //utlum
    float constant{};
    float linear{};
    float quadratic{};

    float cuttOf{};

public:
    Light();
    Light(glm::vec4 color);
    Light(LightType type, glm::vec3 position, glm::vec4 color);

    ~Light();
    void updateStrength(float strength);
    void updateColor(glm::vec4 color);
    void updateShiness(int shiness);
    //void update(ShaderProgram* sh);

    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    glm::vec4 getColor();
    float getStrength() const;
    int getShiness() const;
    LightType getType();


    //
    __attribute__((unused)) void updateDirection(glm::vec3 direction);

    __attribute__((unused)) void updatePosition(glm::vec3 position);

    __attribute__((unused)) void updateCutOff(float cutOff);
    float getCutOff() const;
    glm::vec3 getDirection();
    glm::vec3 getPosition();

};
