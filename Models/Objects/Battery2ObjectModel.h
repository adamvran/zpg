#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/Battery/battery2.obj"
class Battery2ObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    Battery2ObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};