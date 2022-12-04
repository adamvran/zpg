#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/Terrain/teren.obj"
class TerrainObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    TerrainObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};