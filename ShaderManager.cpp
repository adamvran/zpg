#include "ShaderManager.h"

ShaderManager::ShaderManager() {
    this->shader_arr = new GLuint[10];
    this->count_shaders = 0;
}
ShaderManager::~ShaderManager() = default;

void ShaderManager::addShader(GLuint id_shader){
    this->shader_arr[this->count_shaders] = id_shader;
    this->count_shaders++;
}

void ShaderManager::initShaders(){
    this->shader_program = glCreateProgram();
    for (int i = 0; i < this->count_shaders; i++)
        glAttachShader(this->shader_program, this->shader_arr[i]);
    glLinkProgram(this->shader_program);
}

void ShaderManager::checkStatus() const{
    GLint status;
    glGetProgramiv(this->shader_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(this->shader_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->shader_program, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void ShaderManager::init() const
{
    glUseProgram(this->shader_program);
}
