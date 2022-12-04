#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/Battery/battery.obj"
class BatteryObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    BatteryObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};