//Include GLEW
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"


#include "lib/glm/glm/vec3.hpp"
#include "lib/glm/glm/vec4.hpp"
#include "lib/glm/glm/mat4x4.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"
//Include the standard C++ headers  
#include <cstdlib>
#include <cstdio>
#include "Application.h"
#include "Shader.h"
#include "TransformationType.h"
#include "Loader.h"
//include models
#include "TreeModel.h"
#include "BushModel.h"
#include "GiftModel.h"
#include "PlaneModel.h"
#include "MonkeyModel.h"
#include "SphereModel.h"



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

    //basic
    string fShaderBasic = loader->load("../shaders/fragment/basic.txt");
    __attribute__((unused)) const char* fragmentShaderBasic = fShaderBasic.c_str();

    //basic
    string fShaderBasic2 = loader->load("../shaders/fragment/basic2.txt");
    __attribute__((unused)) const char* fragmentShaderBasic2 = fShaderBasic2.c_str();

    //lambert
    string fShaderLambert = loader->load("../shaders/fragment/lambert.txt");
    __attribute__((unused)) const char* fragmentShaderLambert = fShaderLambert.c_str();

    /*
    __attribute__((unused)) auto* plain = const_cast<float*> (plain);
    __attribute__((unused)) int plainPointsSize = sizeof(plain);
  */

    glm::vec3 cameraEye = glm::vec3(0.0f, 50.0f, 5.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, -1.0f, 0.0f); //nefunguje
	application->createCamera(cameraEye, cameraDir);

    ///vytváření objektů

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
