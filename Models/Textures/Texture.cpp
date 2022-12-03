#include "Texture.h"
#include "../../stb_image.h"
#include <utility>


Texture::Texture()
{
    this->textureID = 0;
}

Texture::Texture(std::vector<std::string> paths, int index)
{
    this->textureID = 0;
    this->paths = std::move(paths);
    this->createTexture(index); //dangerous, but whatever
}

void Texture::createTexture(int index)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(this->paths[0].c_str(), &width, &height, &nrChannels, 3);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.


/*
    if (this->paths.size() != 1)
    {
        std::cout << "Heeeey. Whats up?! Not enoght paths or too much paths. Fix it. NOW!" << std::endl;
        exit(1);
    }

    glActiveTexture(GL_TEXTURE0);
    this->textureID = SOIL_load_OGL_texture(this->paths[0].c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (this->textureID == NULL) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    */
}