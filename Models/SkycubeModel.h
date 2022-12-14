#pragma once
#include "Models.h"
#include "skycube.h"

class SkycubeModel : public Models
{
public:
    SkycubeModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};

