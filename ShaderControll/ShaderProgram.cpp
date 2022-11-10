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

void ShaderProgram::notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    this->setMatrixView(viewMatrix);
    this->setMatrixProjection(projectionMatrix);

}

void ShaderProgram::notify(Camera* camera)
{
    this->setMatrixModel(camera->getViewMatrix());
    this->setMatrixProjection(camera->getProjectionMatrix());
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
        case MatrixType::ALL:
            break;
        case MatrixType::TRANSFORM:
            break;
    }
}

void ShaderProgram::notify(MatrixType type)
{
    switch (type)
    {
        case MatrixType::VIEWMATRIX:
            this->setMatrixView(this->activeCamera->getViewMatrix());
            break;
        case MatrixType::PROJECTIONMATRIX:
            this->setMatrixProjection(this->activeCamera->getProjectionMatrix());
            break;

        case MatrixType::ALL:
            this->setMatrixView(this->activeCamera->getViewMatrix());
            this->setMatrixProjection(this->activeCamera->getProjectionMatrix());
            break;
        case MatrixType::TRANSFORM:
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

__attribute__((unused)) void ShaderProgram::setStrength(float strength) const {
    this->run();
    GLint idStrength = glGetUniformLocation(this->shaderProgram, "strength");
    glUniform1f(idStrength, strength);
}

__attribute__((unused)) void ShaderProgram::setColor(glm::vec4 color) const {
    this->run();
    GLint idColor = glGetUniformLocation(this->shaderProgram, "myColor");
    glUniform4fv(idColor, 1, &color[0]); //zkusit 1, 2 ,3 ještě
}

void ShaderProgram::setShiness(int shiness) const {
    this->run();
    GLint idShiness = glGetUniformLocation(this->shaderProgram, "shiness");
    glUniform1i(idShiness, shiness);
}

void ShaderProgram::setActiveCamera(Camera* camera)
{
    this->activeCamera = camera;
}

void ShaderProgram::setActualLight(GLint count) const
{
    this->run();
    GLint idcount = glGetUniformLocation(this->shaderProgram, "currentLights");
    glUniform1i(idcount, count);
}

void ShaderProgram::updateLights(std::vector<Light*> lights) const
{
    this->run();
    this->setActualLight(lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        GLuint loc1 = glGetUniformLocation(this->shaderProgram,("lights[" + index + "].position").c_str());
        glUniform3fv(loc1, 1, &lights[i]->getPosition()[0]);

        GLuint loc2 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].direction").c_str());
        glUniform3fv(loc2, 1, &lights[i]->getDirection()[0]);

        GLuint loc3 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].color").c_str());
        glUniform4fv(loc3, 1, &lights[i]->getColor()[0]);

        GLuint loc4 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].strength").c_str());
        glUniform1f(loc4, lights[i]->getStrength());

        GLuint loc5 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].shiness").c_str());
        glUniform1i(loc5, lights[i]->getShiness());

        //toto osetrit
        int type = 0;
        switch (lights[i]->getType())
        {
            case LightType::POINT:
                type = 1;
                break;
            case LightType::SPOT:
                type = 2;
                break;
            case LightType::DIRECTION:
                type = 3;
                break;
        }
        GLuint loc6 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].type").c_str());
        glUniform1i(loc6, type);

        GLuint loc7 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].constant").c_str());
        glUniform1f(loc7, lights[i]->getConstant());

        GLuint loc8 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].linear").c_str());
        glUniform1f(loc8, lights[i]->getLinear());

        GLuint loc9 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].quadratic").c_str());
        glUniform1f(loc9, lights[i]->getQuadratic());

        if (lights[i]->getType() == LightType::SPOT)
        {
            GLuint loc10 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].cutOff").c_str());
            glUniform1f(loc10, lights[i]->getCutOff());
        }
    }
}

void ShaderProgram::updatePointLights(std::vector<PointLight*> lights) const
{
    this->run();
    this->setActualLight(lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        GLuint loc1 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].position").c_str());
        glUniform3fv(loc1, 1, &lights[i]->getPosition()[0]);

        GLuint loc3 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].color").c_str());
        glUniform4fv(loc3, 1, &lights[i]->getColor()[0]);

        GLuint loc4 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].strength").c_str());
        glUniform1f(loc4, lights[i]->getStrength());

        GLuint loc5 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].shiness").c_str());
        glUniform1i(loc5, lights[i]->getShiness());

        //toto osetrit
        int type = 0;
        switch (lights[i]->getType())
        {
            case LightType::POINT:
                type = 1;
                break;
            case LightType::SPOT:
                type = 2;
                break;
            case LightType::DIRECTION:
                type = 3;
                break;
        }
        GLuint loc6 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].type").c_str());
        glUniform1i(loc6, type);

        GLuint loc7 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].constant").c_str());
        glUniform1f(loc7, lights[i]->getConstant());

        GLuint loc8 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].linear").c_str());
        glUniform1f(loc8, lights[i]->getLinear());

        GLuint loc9 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].quadratic").c_str());
        glUniform1f(loc9, lights[i]->getQuadratic());
    }
}

void ShaderProgram::updateSpotLights(std::vector<SpotLight*> lights) const
{
    this->run();
    this->setActualLight(lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        GLuint loc1 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].position").c_str());
        glUniform3fv(loc1, 1, &lights[i]->getPosition()[0]);

        GLuint loc2 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].direction").c_str());
        glUniform3fv(loc2, 1, &lights[i]->getDirection()[0]);

        GLuint loc3 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].color").c_str());
        glUniform4fv(loc3, 1, &lights[i]->getColor()[0]);

        GLuint loc4 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].strength").c_str());
        glUniform1f(loc4, lights[i]->getStrength());

        GLuint loc5 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].shiness").c_str());
        glUniform1i(loc5, lights[i]->getShiness());

        //toto osetrit
        int type = 0;
        switch (lights[i]->getType())
        {
            case LightType::POINT:
                type = 1;
                break;
            case LightType::SPOT:
                type = 2;
                break;
            case LightType::DIRECTION:
                type = 3;
                break;
        }
        GLuint loc6 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].type").c_str());
        glUniform1i(loc6, type);

        GLuint loc7 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].constant").c_str());
        glUniform1f(loc7, lights[i]->getConstant());

        GLuint loc8 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].linear").c_str());
        glUniform1f(loc8, lights[i]->getLinear());

        GLuint loc9 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].quadratic").c_str());
        glUniform1f(loc9, lights[i]->getQuadratic());

        GLuint loc10 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].cutOff").c_str());
        glUniform1f(loc10, lights[i]->getCutOff());
    }
}

void ShaderProgram::updateDirLights(std::vector<DirectionalLight*> lights) const
{
    this->run();
    this->setActualLight(lights.size());
    for (int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);

        GLuint loc2 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].direction").c_str());
        glUniform3fv(loc2, 1, &lights[i]->getDirection()[0]);

        GLuint loc3 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].color").c_str());
        glUniform4fv(loc3, 1, &lights[i]->getColor()[0]);

        GLuint loc4 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].strength").c_str());
        glUniform1f(loc4, lights[i]->getStrength());

        GLuint loc5 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].shiness").c_str());
        glUniform1i(loc5, lights[i]->getShiness());

        //toto osetrit
        int type = 0;
        switch (lights[i]->getType())
        {
            case LightType::POINT:
                type = 1;
                break;
            case LightType::SPOT:
                type = 2;
                break;
            case LightType::DIRECTION:
                type = 3;
                break;
        }
        GLuint loc6 = glGetUniformLocation(this->shaderProgram, ("lights[" + index + "].type").c_str());
        glUniform1i(loc6, type);
    }
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
