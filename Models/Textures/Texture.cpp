#include "Texture.h"

#include <utility>

Texture::Texture()
{
    this->textureID = 0;
}

Texture::Texture(std::vector<std::string> paths, int index)
{
    this->textureID = 0;
    this->paths = std::move(paths);
    this->createTexture(index);
}

void Texture::createTexture(int index)
{
    if (this->paths.size() != 1)
    {
        std::cout << "Heeeey. Whats up?! Not enoght paths or too much paths. Fix it. NOW!" << std::endl;
        exit(1);
    }

    glActiveTexture(GL_TEXTURE0 + index);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    this->textureID = SOIL_load_OGL_texture(this->paths[0].c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (this->textureID == 0) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}