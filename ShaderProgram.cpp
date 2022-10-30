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
    this->run();
    GLint idModelTransform = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::notify(MatrixType matrixType, glm::mat4 matrix)
{
    switch (matrixType) {
        case MatrixType::PROJECTIONMATRIX:
            this->setMatrixProjection(matrix);
            break;

        case MatrixType::VIEWMATRIX:
            this->setMatrixView(matrix);
            break;
    }
}

void ShaderProgram::setMatrixView(glm::mat4 mat) const
{
    this->run();
    GLint idViewMatrix = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMatrixProjection(glm::mat4 mat) const
{
    this->run();
    GLint idProjectionMatrix = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::run() const
{
    glUseProgram(this->shaderProgram);
}

void ShaderProgram::setStrength(float strength) const {
    this->run();
    GLint idStrength = glGetUniformLocation(this->shaderProgram, "strength");
    glUniform1f(idStrength, strength);
}

void ShaderProgram::setColor(glm::vec4 color) const {
    this->run();
    GLint idColor = glGetUniformLocation(this->shaderProgram, "myColor");
    glUniform4fv(idColor, 1, &color[0]); //zkusit 1, 2 ,3 ještě
}

void ShaderProgram::setShiness(int shiness) const {
    this->run();
    GLint idShiness = glGetUniformLocation(this->shaderProgram, "shiness");
    glUniform1i(idShiness, shiness);
}


/*
void ShaderProgram::update(int message){
    setShader();
    id(message == VIEWMATRIX){
        sendUniform("view", this->camera->getViewMatrix);
    }
    id(message == PROJECTIONMATRIX){
        sendUniform("view", this->camera->getViewMatrix);
    }
}
*/
