#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/House/model.obj"
class HouseObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    HouseObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};