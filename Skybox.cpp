#include "Skybox.h"

#include <utility>

Skybox::Skybox()
{
    this->textureID = 0;
}

Skybox::Skybox(std::vector<std::string> paths, int index)
{
    this->textureID = 0;
    this->paths = std::move(paths);
    this->createTexture(index);
}

void Skybox::createTexture(int index)
{
    if (this->paths.size() != 6)
    {
        std::cout << "Heeeey. Whats up?! Not enoght paths or too much paths. Fix it. NOW!" << std::endl;
        exit(1);
    }

    glActiveTexture(GL_TEXTURE0 + index);
    this->textureID = SOIL_load_OGL_cubemap(this->paths[0].c_str(), this->paths[1].c_str(), this->paths[2].c_str(), 
        this->paths[3].c_str(), this->paths[4].c_str(), this->paths[5].c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (this->textureID == 0) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
