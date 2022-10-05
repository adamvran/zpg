#pragma once
#include "ShaderManager.h"
class Shader {
private:
    GLuint id_shader{};
    GLenum type_shader;
    const char* shader;

public:
    Shader(GLenum type_shader, const char* shader);
    ~Shader();
    void createShader(ShaderManager* manager);
};