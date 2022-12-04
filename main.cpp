
#include <iostream>
#include "Application.h"
#include "Loader.h"
#include "Models/Textures/PlaneTextureModel.h"
#include "Models/Textures/SkyboxTextureModel.h"
#include "Models/SuziFlatModel.h"
#include "Models/Objects/HouseObjectModel.h"
#include "Models/Objects/PlainObjectModel.h"
#include "Models/Objects/TerrainObjectModel.h"
#include "Models/Objects/TreeObjectModel.h"


TransformationType shift = TransformationType::Shift;
TransformationType scale = TransformationType::Scale;

int main()
{
    //rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
    //posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
    //zvetseni: sc, glm::vec3(0.3f)
    srand(time(nullptr));
    auto* application = new Application(800, 600, "ZPG");

    vector<string> skybox = {
            "../Models/Textures/skybox/posx.jpg",
            "../Models/Textures/skybox/negx.jpg",
            "../Models/Textures/skybox/posy.jpg",
            "../Models/Textures/skybox/negy.jpg",
            "../Models/Textures/skybox/posz.jpg",
            "../Models/Textures/skybox/negz.jpg"
    };

    std::vector<int> shapes;
    auto* loader = new Loader();

    //SKYBOX
    string vShaderSkybox = loader->load("../shaders/vertex/skybox.vsh");
    const char* vertexSKYBOX = vShaderSkybox.c_str();
    string fShaderSkybox = loader->load("../shaders/fragment/skybox.frag");
    const char* fragmentSKYBOX = fShaderSkybox.c_str();

    shapes.push_back((int)application->createNewObject(new SkyboxTextureModel(), vertexSKYBOX, fragmentSKYBOX, skybox));
    application->transformObject(shapes[0], scale, glm::vec3(20.0));

    string vShader = loader->load("../shaders/vertex/lightTexture.vsh");
    const char* vertexShaderTexture = vShader.c_str();
    string fShader5 = loader->load("../shaders/fragment/texture.frag");
    const char* fragmentShaderTexture = fShader5.c_str();
    string fShader8 = loader->load("../shaders/fragment/blinnLights.frag");
    const char* fragmentShaderLIGHTS = fShader8.c_str();

    //camera
    glm::vec3 cameraEye = glm::vec3(0.0f, 0.5f, 4.0f);
    glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
    application->createCamera(cameraEye, cameraDir);
    application->createLights(LightType::POINT);

    auto* monkey = new SuziFlatModel();

    //plane with texture
    shapes.push_back((int)application->createNewObject(new PlaneTextureModel(), vertexShaderTexture, fragmentShaderTexture, "../Models/Textures/wooden_fence.png"));
    application->transformObject(shapes.at(1), scale, glm::vec3(5));
    application->transformObject(shapes.at(1), glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));

    for (int i = 0; i < 5; i++)
        shapes.push_back((int)application->createNewObject(monkey, vertexShaderTexture, fragmentShaderLIGHTS));

    for (int i = 2; i < shapes.size(); i++)
    {
        application->transformObject(shapes[i], scale, glm::vec3(0.4));
        application->transformObject(shapes[i], shift, glm::vec3((-3.f) - (float)(rand() % 60) + 1.0f, 1.0f, (-3.f) - (float)(rand() % 60) + (float)i));
    }


    int terrain = (int)application->createNewObject(new TerrainObjectModel(), vertexShaderTexture, fragmentShaderTexture, "../Models/Objects/Terrain/grass.png");
    application->transformObject(terrain, scale, glm::vec3(2));
    //application->transformObject(plain, 90.0f, glm::vec3(5, 0, -5));

    int house = (int)application->createNewObject(new HouseObjectModel(), vertexShaderTexture, fragmentShaderTexture, "../Models/Objects/House/house.png");
    application->transformObject(house, scale, glm::vec3(1));
    application->transformObject(house, shift, glm::vec3(5, 0, -15));


    int tree = (int)application->createNewObject(new TreeObjectModel(), vertexShaderTexture, fragmentShaderTexture, "../Models/Objects/Tree/tree.png");
    application->transformObject(tree, scale, glm::vec3(1));
    application->transformObject(tree, shift, glm::vec3(5, 0, 15));


    application->run();
    application->~Application();
    exit(EXIT_SUCCESS);
}
