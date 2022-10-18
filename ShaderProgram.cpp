#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->shaderManager = new ShaderManager();
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::inicializeShaders()
{
    this->shaderProgram = glCreateProgram();
    this->shaderManager->initShaders(this->shaderProgram);
    glLinkProgram(this->shaderProgram);
}

void ShaderProgram::checkStatus()
{
    GLint status;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

}

void ShaderProgram::createShader(GLenum shaderType, const char* shaderDefinition)
{
    this->shaderManager->createShader(shaderType, shaderDefinition);
}

void ShaderProgram::setMatrixModel(glm::mat4 mat)
{
    GLint idModelTransform = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &mat[0][0]);

   /* ///kamera
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); ///projekèní matice, magic uvnitø -> úhel pod kterým se dívám na objekt, èím vìtší je, tím je i objekt menší
    glm::mat4 viewMatrix = glm::lookAt( //pohledová matice, hodnoty eye, center a up se mìní
        glm::vec3(1.0, 1.0, 1.0), //kde je kamera
        glm::vec3(0.0, 0.0, 0.0), //kde je bod, kam se divam
        glm::vec3(0.0, 1.0, 0.0) //kdybych chtel obratit, dam -1 (kde je bod smìrem vzhùru od kamery)
    );*/

}

void ShaderProgram::notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    this->setMatrixView(viewMatrix);
    this->setMatrixProjection(projectionMatrix);
    
}

void ShaderProgram::setMatrixView(glm::mat4 mat)
{
    ///odelsání pohledové matice do shaderu
    GLint idViewMatrix = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &mat[0][0]);

}

void ShaderProgram::setMatrixProjection(glm::mat4 mat)
{
    ///odeslání projekèní matice do shaderu
    GLint idProjectionMatrix = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::run()
{
    glUseProgram(this->shaderProgram);
}