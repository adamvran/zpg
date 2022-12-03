#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/Plain/plain.obj"

class PlainObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    PlainObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};

