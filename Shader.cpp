#include "Shader.h"

Shader::Shader(GLenum type_shader, const char* shader) {
    this->type_shader = type_shader;
    this->shader = shader;
}
Shader::~Shader() = default;

void Shader::createShader(ShaderManager* manager) {
    this->id_shader = glCreateShader(this->type_shader);
    glShaderSource(this->id_shader, 1, &this->shader, nullptr);
    glCompileShader(this->id_shader);
    manager->addShader(this->id_shader);
}
