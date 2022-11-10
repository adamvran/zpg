
#include <iostream>
#include "Application.h"
#include "Loader.h"
#include "Models/Textures/PlaneTextureModel.h"
#include "Models/Textures/SkyboxTextureModel.h"
#include "Models/SuziFlatModel.h"


TransformationType shift = TransformationType::Shift;
TransformationType scale = TransformationType::Scale;

int main(void)
{
    //rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
    //posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
    //zvetseni: sc, glm::vec3(0.3f)
    srand(time(NULL));
    Application* application = new Application(800, 600, "ZPG");

    vector<string> skybox = {
            "../Models/Textures/skybox/posx.jpg",
            "../Models/Textures/skybox/negx.jpg",
            "../Models/Textures/skybox/posy.jpg",
            "../Models/Textures/skybox/negy.jpg",
            "../Models/Textures/skybox/posz.jpg",
            "../Models/Textures/skybox/negz.jpg"
    };


    Loader* loader = new Loader();
    //blinn
    string vShader = loader->load("../shaders/vertex/light.vsh");
    string fShader = loader->load("../shaders/fragment/blinn2.txt");
    const char* vertexShader = vShader.c_str();
    __attribute__((unused)) const char* fragmentShader = fShader.c_str();

    //phong
    string fShader2 = loader->load("../shaders/fragment/phong.txt");
    __attribute__((unused)) const char* fragmentShaderPHONG = fShader2.c_str();

    //lambert
    string fShader3 = loader->load("../shaders/fragment/lambert.txt");
    __attribute__((unused)) const char* fragmentShaderLAMBERT = fShader3.c_str();

    //basic
    string fShader4 = loader->load("../shaders/fragment/basic.txt");
    __attribute__((unused)) const char* fragmentShaderBASIC = fShader4.c_str();

    //basic2
    string fShader5 = loader->load("../shaders/fragment/basic2.frag");
    const char* fragmentShaderBASIC2 = fShader5.c_str();

    //phongwrong
    string fShader6 = loader->load("../shaders/fragment/phongWrong.txt");
    __attribute__((unused)) const char* fragmentShaderPHONGWRONG = fShader6.c_str();

    //skybox fragment a vertex
    string fShader7 = loader->load("../shaders/fragment/basicSKYBOX.frag");
    __attribute__((unused)) const char* fragmentSKYBOX = fShader7.c_str();

    string vShader7 = loader->load("../shaders/vertex/lightSKYBOX.vsh");
    __attribute__((unused)) const char* vertexSKYBOX = vShader7.c_str();


    //phong good
    //string fShader7 = loader->load("../shaders/fragment/phongGood.txt");
    /*string fShader7 = loader->load("../shaders/fragment/blinnLights.h");
    const char* fragmentShaderPHONGGOOD = fShader7.c_str();*/

    string fShader8 = loader->load("../shaders/fragment/blinnLights.frag");
    const char* fragmentShaderLIGHTS = fShader8.c_str();

    //camera
    glm::vec3 cameraEye = glm::vec3(0.0f, 0.5f, 4.0f);
    glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
    application->createCamera(cameraEye, cameraDir);
    application->createLights(LightType::POINT);

    auto* monkey = new SuziFlatModel();

    std::vector<int> shapes;
    shapes.push_back(application->createNewObject(new PlaneTextureModel(), vertexShader, fragmentShaderBASIC2, "../Models/Textures/wooden_fence.png"));
    application->transformObject(shapes.at(0), scale, glm::vec3(200));
    //shapes.push_back(application->createNewObject(new PlaneTextureModel(), vertexShader, fragmentShaderBASIC2, "../models/textures/grass.png"));
    //shapes.push_back(application->createNewObject(new PlaneModel(), vertexShader, fragmentShaderBASIC));
    /*application->transformObject(shapes[0], scale, glm::vec3(50.0));
    application->transformObject(shapes[0], shift, glm::vec3(0.0, 0.0, 0.0));

    application->transformObject(shapes[1], scale, glm::vec3(50.0));
    application->transformObject(shapes[1], shift, glm::vec3(2.0, 0.0, 0.0));*/

    //skybox
    //shapes.push_back(application->createNewObject(new SkyboxTextureModel(), vertexSKYBOX, fragmentSKYBOX, skybox));
    //application->transformObject(shapes[1], scale, glm::vec3(20.0));

    for (int i = 0; i < 5; i++)
    {
        shapes.push_back(application->createNewObject(monkey, vertexShader, fragmentShaderLIGHTS));
    }

    for (int i = 2; i < shapes.size(); i++)
    {
        application->transformObject(shapes[i], scale, glm::vec3(0.4));
        application->transformObject(shapes[i], shift, glm::vec3((-3.f) - (float)(rand() % 60) + i, 1.0f, (-3.f) - (float)(rand() % 60) + i));

    }



    application->run();
    application->~Application();
    exit(EXIT_SUCCESS);
}
