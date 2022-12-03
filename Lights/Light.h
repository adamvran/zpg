#pragma once

#include "../lib/glm/glm/vec4.hpp"
#include "../ShaderControll/ShaderProgram.h"
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
    explicit Light(glm::vec4 color);
    Light(LightType type, glm::vec3 position, glm::vec4 color);

    ~Light();

    __attribute__((unused)) void updateStrength(float strength_);
    __attribute__((unused)) void updateColor(glm::vec4 color_);
    __attribute__((unused)) void updateShiness(int shiness_);
    //void update(ShaderProgram* sh);

    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    glm::vec4 getColor();
    float getStrength() const;
    int getShiness() const;
    LightType getType();


    //
    __attribute__((unused)) void updateDirection(glm::vec3 direction_);

    __attribute__((unused)) void updatePosition(glm::vec3 position_);

    __attribute__((unused)) void updateCutOff(float cutOff);
    float getCutOff() const;
    glm::vec3 getDirection();
    glm::vec3 getPosition();

};
