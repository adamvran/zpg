#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->shaderManager = new ShaderManager();
}

ShaderProgram::~ShaderProgram() = default;

void ShaderProgram::inicializeShaders()
{
    this->shaderProgram = glCreateProgram();
    this->shaderManager->initShaders(this->shaderProgram);
    glLinkProgram(this->shaderProgram);
}

void ShaderProgram::checkStatus() const
{
    GLint status;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->shaderProgram, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

}

void ShaderProgram::createShader(GLenum shaderType, const char* shaderDefinition)
{
    this->shaderManager->createShader(shaderType, shaderDefinition);
}

void ShaderProgram::setMatrixModel(glm::mat4 mat) const
{
    GLint idModelTransform = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const
{
    this->setMatrixView(viewMatrix);
    this->setMatrixProjection(projectionMatrix);
}

void ShaderProgram::setMatrixView(glm::mat4 mat) const
{
    GLint idViewMatrix = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMatrixProjection(glm::mat4 mat) const
{
    GLint idProjectionMatrix = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::run() const
{
    glUseProgram(this->shaderProgram);
}