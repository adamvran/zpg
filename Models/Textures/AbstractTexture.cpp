#include "AbstractTexture.h"

AbstractTexture::AbstractTexture()
{
    this->textureID = 0;
}

GLuint AbstractTexture::getTexture() const
{
    return this->textureID;
}
