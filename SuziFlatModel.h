#pragma once
#include "Models/suzi_flat.h"
#include "Models.h"

class SuziFlatModel : public Models
{
public:
    SuziFlatModel();
    void createVBO() override;
    void createVAO() override;
    void drawObject() override;
    void initPositionAndColor() override;
};
