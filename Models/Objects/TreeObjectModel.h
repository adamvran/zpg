#pragma once
#include "../Models.h"
#include "LoaderObject.h"

#define PATH "../Models/Objects/Tree/tree.obj"
class TreeObjectModel : public Models
{
private:
    LoaderObject* loader;
    std::vector<float> data;
public:
    TreeObjectModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};