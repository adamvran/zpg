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
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/plain.h"
//#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/tree.h"

int main()
{
	//rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
	//posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
	//zvetseni: sc, glm::vec3(0.3f)

	auto* application = new Application(1300, 900, "ZPG");
    __attribute__((unused)) TransformationType sh = TransformationType::Shift;
    __attribute__((unused)) TransformationType sc = TransformationType::Scale;

    auto* loader = new Loader;
    string vShader = loader->load("/Users/adamvrana/CLionProjects/zpg/cviceni2 2/shaders/vertex/light.txt");
    string fShader = loader->load("/Users/adamvrana/CLionProjects/zpg/cviceni2 2/shaders/fragment/blinn.txt");
    const char* vertexShader = vShader.c_str();
    const char* fragmentShader = fShader.c_str();

    auto* giftPoints = const_cast<float*> (gift);
    int giftPointsSize = sizeof(gift);

    auto* spherePoints = const_cast<float*> (sphere);
    int spherePointsSize = sizeof(sphere);

    auto* treePoints = const_cast<float*> (tree);
    int treePointsSize = sizeof(tree);


    glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, 4.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
	application->createCamera(cameraEye, cameraDir);

    ///vytváření objektů

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


    application->run();
	application->~Application();
	exit(EXIT_SUCCESS);
}
