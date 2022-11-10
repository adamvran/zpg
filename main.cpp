//Include the standard C++ headers
#include <cstdlib>
#include "Application.h"
#include "ShaderControll/Shader.h"
#include "Transformations/TransformationType.h"
#include "Loader.h"
//include models
#include "Models/TreeModel.h"
#include "Models/BushesModel.h"
#include "Models/GiftModel.h"
#include "Models/PlainModel.h"
#include "Models/SuziSmoothModel.h"
#include "Models/SuziFlatModel.h"
#include "Models/SphereModel.h"



int main()
{
	//rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
	//posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
	//zvetseni: sc, glm::vec3(0.3f)

	auto* application = new Application(1300, 900, "ZPG");
    __attribute__((unused)) TransformationType sh = TransformationType::Shift;
    __attribute__((unused)) TransformationType sc = TransformationType::Scale;

    auto* loader = new Loader;

    string vShaderLight = loader->load("../shaders/vertex/light.txt");
    const char* vertexShader = vShaderLight.c_str();

    //blinn
    string fShaderBlinn = loader->load("../shaders/fragment/blinn.txt");
    __attribute__((unused)) const char* fragmentShaderBlinn = fShaderBlinn.c_str();

    //phong
    string fShaderPhong = loader->load("../shaders/fragment/phong.txt");
    __attribute__((unused)) const char* fragmentShaderPhong = fShaderPhong.c_str();
    //phong good
    string fShaderPhongGood = loader->load("../shaders/fragment/phong_good.txt");
    __attribute__((unused)) const char* fragmentShaderPhongGood = fShaderPhongGood.c_str();
    //phong wrong
    string fShaderPhongWrong = loader->load("../shaders/fragment/phong_wrong.txt");
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

    glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, 4.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, -1.0f, 0.0f); //uz working
	application->createCamera(cameraEye, cameraDir);
    ///vytváření objektů

    cout << "\n\nPrvni ukol - 1\nDruhy ukol - 2\nTreti ukol - 3\nInput: ";
    int input;
    cin >> input;


    std::vector<int> objects;
    int sphere_o;
    switch (input)
    {
        case 1:
            for (int i = 0; i < 4; i++)
                objects.push_back(application->createNewObject(new SphereModel(), vertexShader, fragmentShaderPhong));

            for (int i = 0; i < 4; i++)
                application->transformObject(objects[i], sc, glm::vec3(0.3));

            application->transformObject(objects[0], sh, glm::vec3(-3.f, 0.0f, 0.0f));
            application->transformObject(objects[1], sh, glm::vec3(3.f, 0.0f, 0.0f));
            application->transformObject(objects[2], sh, glm::vec3(0.f, -3.0f, 0.0f));
            application->transformObject(objects[3], sh, glm::vec3(0.f, 3.0f, 0.0f));
            break;

        case 2:
            sphere_o = application->createNewObject(new SphereModel(), vertexShader, fragmentShaderPhongWrong); //fragmentShaderPhongGood
            application->transformObject(sphere_o, sc, glm::vec3(0.3));
            application->transformObject(sphere_o, sh, glm::vec3(0.0f, 0.0f, 5.0f));
            break;

        case 3:
            objects.push_back(application->createNewObject(new PlainModel(), vertexShader, fragmentShaderBlinn));
            for (int i = 0; i < 100; i++)
            {
                objects.push_back(application->createNewObject(new TreeModel(), vertexShader, fragmentShaderBasic));
                objects.push_back(application->createNewObject(new SphereModel(), vertexShader, fragmentShaderBasic2));
                objects.push_back(application->createNewObject(new GiftModel(), vertexShader, fragmentShaderLambert));
                objects.push_back(application->createNewObject(new BushesModel(), vertexShader, fragmentShaderBlinn));
                objects.push_back(application->createNewObject(new SuziSmoothModel(), vertexShader, fragmentShaderPhong));
                objects.push_back(application->createNewObject(new SuziFlatModel(), vertexShader, fragmentShaderLambert));
            }

            application->transformObject(objects[0], sc, glm::vec3(100.0));
            application->transformObject(objects[0], sh, glm::vec3(0.0, 0.00001, 0.0));
            for (int i = 1; i < objects.size(); i++)
            {
                application->transformObject(objects[i], sc, glm::vec3(0.1));
                application->transformObject(objects[i], sh, glm::vec3((0.f) - (float)(rand() % 300), 1.0f, - (float)(rand() % 300)));
            }
            break;
        default:
            cout << "bad input" << endl;
            break;
    }
    /*
    //sphere
    std::vector<int> spheres;
    spheres.reserve(1);
    for (int i = 0; i < 1; ++i)
    {
        spheres.push_back(application->createNewObject(new SphereModel(), vertexShader, fragmentShaderBasic));
        application->transformObject(spheres.back(), sc, glm::vec3(0.3));
        application->transformObject(spheres.back(), sh, glm::vec3((0.f) - (float) (rand() % 200), 0.0f, -(float) (rand() % 200)));
    }

    //plain
    std::vector<int> spheres2;
    spheres2.reserve(1);
    for (int i = 0; i < 1; ++i)
    {
        spheres2.push_back(application->createNewObject(new TreeModel(), vertexShader, fragmentShaderBasic2));
        application->transformObject(spheres2.back(), sc, glm::vec3(0.3));
        application->transformObject(spheres2.back(), sh, glm::vec3((0.f) - (float) (rand() % 200), 0.0f, -(float) (rand() % 200)));
    }
*/
    /*
	int gift_o = application->createNewObject(giftPoints, giftPointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 66624);
    application->transformObject(gift_o, sc, glm::vec3(0.3));
    application->transformObject(gift_o, sh, glm::vec3(-3.f, 0.0f, 0.0f));

    int sphere1 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere1, sc, glm::vec3(0.3));
    application->transformObject(sphere1, sh, glm::vec3(3.f, 0.0f, 0.0f));

	int tree_o = application->createNewObject(treePoints, treePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 92814);
    application->transformObject(tree_o, sc, glm::vec3(0.3));
    application->transformObject(tree_o, sh, glm::vec3(0.f, 3.0f, 0.0f));

    int sphere2 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere2, sc, glm::vec3(0.3));
    application->transformObject(sphere2, sh, glm::vec3(0.f, -3.0f, 0.0f));
*/

    ///4 kuličky
    /*
    int sphere3 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere3, sc, glm::vec3(0.3));
    application->transformObject(sphere3, sh, glm::vec3(-3.f, 0.0f, 0.0f));

    int sphere1 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere1, sc, glm::vec3(0.3));
    application->transformObject(sphere1, sh, glm::vec3(3.f, 0.0f, 0.0f));

    int sphere4 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere4, sc, glm::vec3(0.3));
    application->transformObject(sphere4, sh, glm::vec3(0.f, 3.0f, 0.0f));

    int sphere2 = application->createNewObject(spherePoints, spherePointsSize, vertexShader, fragmentShader, GL_TRIANGLES, 2880);
    application->transformObject(sphere2, sc, glm::vec3(0.3));
    application->transformObject(sphere2, sh, glm::vec3(0.f, -3.0f, 0.0f));
*/
    application->run();
	application->~Application();
	exit(EXIT_SUCCESS);
}
