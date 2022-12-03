#include "Skybox.h"

#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Skybox::Skybox()
{
    this->textureID = 0;
}

Skybox::Skybox(std::vector<std::string> paths, int index)
{
    this->textureID = 0;
    this->paths = std::move(paths);
    this->createTexture(index); //dangerous, but whatever
}

void Skybox::createTexture(int index)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;

    for (unsigned int i = 0; i < this->paths.size(); i++)
    {
        unsigned char *data = stbi_load(this->paths[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << this->paths[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

/*
    if (this->paths.size() != 6)
    {
        std::cout << "Heeeey. Whats up?! Not enoght paths or too much paths. Fix it. NOW!" << std::endl;
        exit(1);
    }

    this->textureID = SOIL_load_OGL_cubemap(this->paths[0].c_str(), this->paths[1].c_str(), this->paths[2].c_str(),
        this->paths[3].c_str(), this->paths[4].c_str(), this->paths[5].c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (this->textureID == 0) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glActiveTexture(GL_TEXTURE0 + index);

    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
*/
}
