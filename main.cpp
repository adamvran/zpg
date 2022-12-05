
#include <iostream>
#include "Application.h"
#include "Loader.h"
#include "Models/Textures/PlaneTextureModel.h"
#include "Models/Textures/SkyboxTextureModel.h"
#include "Models/SuziFlatModel.h"
#include "Models/Objects/HouseObjectModel.h"
#include "Models/Objects/TerrainObjectModel.h"
#include "Models/Objects/TreeObjectModel.h"
#include "Models/Objects/BatteryObjectModel.h"
#include "Models/SphereModel.h"
#include "Models/PlainModel.h"
#include "Models/GiftModel.h"
#include "Models/BushesModel.h"
#include "Models/TreeModel.h"
#include "Models/SuziSmoothModel.h"


TransformationType shift = TransformationType::Shift;
TransformationType scale = TransformationType::Scale;

int main()
{
    //rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
    //posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
    //zvetseni: sc, glm::vec3(0.3f)
    srand(time(nullptr));
    auto* application = new Application(800, 600, "BATTERY CATHEDRAL");

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


    string vShader = loader->load("../shaders/vertex/lightTexture.vsh");
    const char* vertexShaderTexture = vShader.c_str();
    string fShader5 = loader->load("../shaders/fragment/texture.frag");
    const char* fragmentShaderTexture = fShader5.c_str();
    string fShader8 = loader->load("../shaders/fragment/blinnLights.frag");
    const char* fragmentShaderLIGHTS = fShader8.c_str();
    string fShader9 = loader->load("../shaders/fragment/blinnLightsTextures.frag");
    const char* fragmentShaderLIGHTSTextures = fShader9.c_str();

    string vShaderLight = loader->load("../shaders/vertex/light.txt");
    const char* vertexShader = vShaderLight.c_str();
    //blinn
    string fShaderBlinn = loader->load("../shaders/fragment/blinn.txt");
    __attribute__((unused)) const char* fragmentShaderBlinn = fShaderBlinn.c_str();
    //phong
    string fShaderPhong = loader->load("../shaders/fragment/phong.txt");
    __attribute__((unused)) const char* fragmentShaderPhong = fShaderPhong.c_str();
    //phong good
    string fShaderPhongGood = loader->load("../shaders/fragment/phongGood.txt");
    __attribute__((unused)) const char* fragmentShaderPhongGood = fShaderPhongGood.c_str();
    //phong wrong
    string fShaderPhongWrong = loader->load("../shaders/fragment/phongWrong.txt");
    __attribute__((unused)) const char* fragmentShaderPhongWrong = fShaderPhongWrong.c_str();
    //basic
    string fShaderBasic = loader->load("../shaders/fragment/basic.txt");
    __attribute__((unused)) const char* fragmentShaderBasic = fShaderBasic.c_str();
    //basic
    string fShaderBasic2 = loader->load("../shaders/fragment/basic2.txt");
    __attribute__((unused)) const char* fragmentShaderBasic2 = fShaderBasic2.c_str();
    //lambert
    string fShaderLambert = loader->load("../shaders/fragment/lambert.txt");
    __attribute__((unused)) const char* fragmentShaderLambert = fShaderLambert.c_str();

    //camera
    glm::vec3 cameraEye = glm::vec3(0.0f, 0.5f, 4.0f);
    glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
    application->createCamera(cameraEye, cameraDir);
    //application->createLights(LightType::POINT);
    application->createLights(LightType::SPOT);

    cout << "\n\nPrvni ukol - 1\nDruhy ukol - 2\nTreti ukol - 3\nFINAL - 4\nInput: ";
    int input;
    cin >> input;
    std::vector<int> objects;
    int sphere_o;
    int sphere_o2;


    switch (input)
    {
        case 1:
            for (int i = 0; i < 5; i++)
                objects.push_back((int)application->createNewObject(new SphereModel(), vertexShader, fragmentShaderPhong));
            for (int i = 1; i < 5; i++)
                application->transformObject(objects[i], scale, glm::vec3(0.3));
            application->transformObject(objects[1], shift, glm::vec3(-3.f, 0.0f, 0.0f));
            application->transformObject(objects[2], shift, glm::vec3(3.f, 0.0f, 0.0f));
            application->transformObject(objects[3], shift, glm::vec3(0.f, -3.0f, 0.0f));
            application->transformObject(objects[4], shift, glm::vec3(0.f, 3.0f, 0.0f));
            break;
        case 2:
            sphere_o = (int)application->createNewObject(new SphereModel(), vertexShader, fragmentShaderPhongWrong); //fragmentShaderPhongGood
            application->transformObject(sphere_o, scale, glm::vec3(0.3));
            application->transformObject(sphere_o, shift, glm::vec3(0.0f, 0.0f, 5.0f));
            sphere_o2 = (int)application->createNewObject(new SphereModel(), vertexShader, fragmentShaderPhongWrong); //fragmentShaderPhongGood
            application->transformObject(sphere_o2, scale, glm::vec3(0.3));
            application->transformObject(sphere_o2, shift, glm::vec3(0.0f, 0.0f, 5.0f));
            break;
        case 3:
            objects.push_back((int)application->createNewObject(new PlainModel(), vertexShader, fragmentShaderBlinn));
            for (int i = 0; i < 100; i++)
            {
                objects.push_back((int)application->createNewObject(new TreeModel(), vertexShader, fragmentShaderBasic));
                objects.push_back((int)application->createNewObject(new SphereModel(), vertexShader, fragmentShaderBasic2));
                objects.push_back((int)application->createNewObject(new GiftModel(), vertexShader, fragmentShaderLambert));
                objects.push_back((int)application->createNewObject(new BushesModel(), vertexShader, fragmentShaderPhong));
                objects.push_back((int)application->createNewObject(new SuziSmoothModel(), vertexShader, fragmentShaderPhong));
                objects.push_back((int)application->createNewObject(new SuziFlatModel(), vertexShader, fragmentShaderLambert));
            }
            application->transformObject(objects[0], scale, glm::vec3(100.0));
            application->transformObject(objects[0], shift, glm::vec3(0.0, 0.00001, 0.0));
            for (int i = 1; i < objects.size(); i++)
            {
                application->transformObject(objects[i], scale, glm::vec3(0.1));
                application->transformObject(objects[i], shift, glm::vec3((0.f) - (float)(rand() % 300), 1.0f, - (float)(rand() % 300)));
            }
            break;
        case 4:
            shapes.push_back((int)(int)application->createNewObject(new SkyboxTextureModel(), vertexSKYBOX, fragmentSKYBOX, skybox));
            application->transformObject(shapes[0], scale, glm::vec3(20.0));

            auto* monkey = new SuziFlatModel();

            //plane with texture
            shapes.push_back((int)application->createNewObject(new PlaneTextureModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Textures/wooden_fence.png"));
            application->transformObject(shapes.at(1), scale, glm::vec3(5));
            application->transformObject(shapes.at(1), glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));

            shapes.push_back((int)application->createNewObject(new PlaneTextureModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Textures/wooden_fence.png"));
            application->transformObject(shapes.at(2), scale, glm::vec3(5));
            application->transformObject(shapes.at(2), shift, glm::vec3(0.0f, 0.0f, -2.0f));
            application->transformObject(shapes.at(2), shift, glm::vec3(0.0f, 0.005f, 0.0f));
            application->transformObject(shapes.at(2), scale, glm::vec3(2));
            application->transformObject(shapes.at(2), glm::radians(90.f), glm::vec3(1.0f,0.0f, 0.0f));

            shapes.push_back((int)application->createNewObject(new PlaneTextureModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Textures/wooden_fence.png"));
            application->transformObject(shapes.at(3), scale, glm::vec3(5));
            application->transformObject(shapes.at(3), shift, glm::vec3(0.0f, 0.0f, -4.0f));
            application->transformObject(shapes.at(3), shift, glm::vec3(0.0f, 0.005f, 0.0f));
            application->transformObject(shapes.at(3), scale, glm::vec3(2));
            application->transformObject(shapes.at(3), glm::radians(90.f), glm::vec3(1.0f,0.0f, 0.0f));

            for (int i = 0; i < 5; i++)
                shapes.push_back((int)application->createNewObject(monkey, vertexShaderTexture, fragmentShaderLIGHTS));

            for (int i = 4; i < shapes.size(); i++)
            {
                application->transformObject(shapes[i], scale, glm::vec3(0.4));
                application->transformObject(shapes[i], shift, glm::vec3((-3.f) - (float)(rand() % 60) + 1.0f, 1.0f, (-3.f) - (float)(rand() % 60) + (float)i));
            }


            int terrain = (int)application->createNewObject(new TerrainObjectModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Objects/Terrain/grass.png");
            application->transformObject(terrain, scale, glm::vec3(2));
            //application->transformObject(plain, 90.0f, glm::vec3(5, 0, -5));

            int house = (int)application->createNewObject(new HouseObjectModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Objects/House/house.png");
            application->transformObject(house, scale, glm::vec3(1));
            application->transformObject(house, shift, glm::vec3(0, 0, -15));

            int z = -90;
            for (int i = 0; i < 5; ++i) {
                int battery = (int)application->createNewObject(new BatteryObjectModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Objects/Battery/battery.jpg");
                application->transformObject(battery, scale, glm::vec3(0.1));
                application->transformObject(battery, shift, glm::vec3(-30, 0, z));
                application->transformObject(battery, glm::radians(90.0f), glm::vec3(-1, 0, 0));
                z-=30;
            }
            z=-90;
            for (int i = 0; i < 5; ++i) {
                int battery = (int)application->createNewObject(new BatteryObjectModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Objects/Battery/battery.jpg");
                application->transformObject(battery, scale, glm::vec3(0.1));
                application->transformObject(battery, shift, glm::vec3(30, 0, z));
                application->transformObject(battery, glm::radians(90.0f), glm::vec3(-1, 0, 0));
                z-=30;
            }

            int my_tree = (int)application->createNewObject(new TreeObjectModel(), vertexShaderTexture, fragmentShaderLIGHTSTextures, "../Models/Objects/Tree/tree.png");
            application->transformObject(my_tree, scale, glm::vec3(1));
            application->transformObject(my_tree, shift, glm::vec3(5, 0, 15));
    }




    application->run();
    application->~Application();
    exit(EXIT_SUCCESS);
}
