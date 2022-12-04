#include "Battery2ObjectModel.h"

Battery2ObjectModel::Battery2ObjectModel()
{
    this->loader = new LoaderObject(PATH);
    std::pair<int, std::vector<float>> data = this->loader->initData();
    this->data = data.second;
    this->sizeOfpoints = this->data.size() * sizeof(float);
    this->countOfVertex = data.first;
    this->objectType = GL_TRIANGLES;
}

void Battery2ObjectModel::createVBO()
{
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->sizeOfpoints, &this->data[0], GL_STATIC_DRAW);
}

void Battery2ObjectModel::createVAO()
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Battery2ObjectModel::drawObject()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(this->objectType, 0, this->countOfVertex);
}

void Battery2ObjectModel::initPositionAndColor()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}