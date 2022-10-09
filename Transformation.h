#pragma once
#include "lib/glm/glm/vec4.hpp" // glm::vec4
#include "lib/glm/glm/mat4x4.hpp" // glm::mat4
#include "lib/glm/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

class Transformation {
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
