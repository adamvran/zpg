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

//include models
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/plain.h"
//#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/tree.h"

using namespace std;

//light blue color


//vertex shader původni
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 aColor;"
"out vec3 ourColor;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"     ourColor = aColor;"
"}";

const char* vertex_shaderCamera =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 aColor;"
"out vec3 ourColor;"
"uniform mat4 transform;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"void main () {"
"     gl_Position = projectionMatrix * viewMatrix * transform * vec4 (vp, 1.0);"
"     ourColor = aColor;"
"}";


//2880
//glDrawArrays(GL_TRIANGLES, 0, 2880);
//Fragment shader
const char* fragment_shadercviko5=
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"
"out vec4 out_Color;"
"void main(void){"
"    vec3 lightPosition= vec3(10.0,10.0,10.0); //správně upravit"
"    float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);"
"    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);"
"    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);"
"    out_Color = ambient + diffuse;"
"}";



const char* vertex_shaderLambert =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "layout(location=1) in vec3 vn;"
        "out vec4 ex_worldPosition;"
        "out vec3 ex_worldNormal;"
        "uniform mat4 transform;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"
        "void main () {"
        "     ex_worldPosition = transform * vec4(vp, 1.0);"
        "     ex_worldNormal = vn;"
        "     gl_Position = (projectionMatrix * viewMatrix * transform) * vec4(vp, 1.0);"
        "}";


const char* fragment_shaderLambert =
        "#version 330\n"
        "in vec4 ex_worldPosition;"
        "in vec3 ex_worldNormal;"
        "out vec4 out_Color;"
        "void main () {"
        "     vec3 lightPosition = vec3 (0.0 ,0.0 ,0.0);"
        "     vec3 lightVector = vec3(lightPosition.x - ex_worldPosition.x, lightPosition.y - ex_worldPosition.y, lightPosition.z - ex_worldPosition.z);"
        "     float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);"
        "     vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);"
        "     vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
        "     out_Color = ambient + diffuse;"
        "}";


const char* fragment_shaderPhong =
        "#version 330\n"
        "in vec4 ex_worldPosition;"
        "in vec3 ex_worldNormal;"
        "out vec4 out_Color;"
        "void main () {"
        "     vec3 lightPosition = vec3 (0.0 ,0.0 ,0.0);"
        "     vec3 lightVector = vec3(lightPosition.x - ex_worldPosition.x, lightPosition.y - ex_worldPosition.y, lightPosition.z - ex_worldPosition.z);"
        "     float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);"
        "     vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);"
        "     vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
        "     float mir = dot(reflect (lightVector , ex_worldNormal ), vec3(0.0, 0.0, -1.0));"
        "     vec4 mirror = vec4(1.0) * max(mir, 0.0);"
        "     out_Color = ambient + diffuse + mirror;"
        "}";


int main()
{
	//rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
	//posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
	//zvetseni: sc, glm::vec3(0.3f)

	auto* application = new Application(1300, 900, "ZPG");
    __attribute__((unused)) TransformationType sh = TransformationType::Shift;
    __attribute__((unused)) TransformationType sc = TransformationType::Scale;
	glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, 4.0f);
	//glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);

	application->createCamera(cameraEye, cameraDir);

    ///vytváření objektů

	int gift_o = application->createNewObject(1, const_cast<float *>(gift), sizeof(gift), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderLambert, fragment_shaderLambert, GL_TRIANGLES, 66624);

    application->transformObject(gift_o, sc, glm::vec3(0.3));
    application->transformObject(gift_o, sh, glm::vec3(-3.f, 0.0f, 0.0f));

    int sphere2 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderLambert, fragment_shaderLambert, GL_TRIANGLES, 2880);

    application->transformObject(sphere2, sc, glm::vec3(0.3));
    application->transformObject(sphere2, sh, glm::vec3(3.f, 0.0f, 0.0f));


	int sphere3 = application->createNewObject(1, const_cast<float *>(tree), sizeof(tree), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderLambert, fragment_shaderLambert, GL_TRIANGLES, 92814);

    application->transformObject(sphere3, sc, glm::vec3(0.3));
    application->transformObject(sphere3, sh, glm::vec3(0.f, 3.0f, 0.0f));

    int sphere4 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderLambert, fragment_shaderPhong, GL_TRIANGLES, 2880);

    application->transformObject(sphere4, sc, glm::vec3(0.3));
    application->transformObject(sphere4, sh, glm::vec3(0.f, -3.0f, 0.0f));


    application->run();
	application->~Application();
	exit(EXIT_SUCCESS);
}
