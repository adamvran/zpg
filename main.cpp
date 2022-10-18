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
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "plain.h"

using namespace std;


//body pro trojuhelník
/*float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};*/


//body pro ctverec
/*float points[] = {
	0.5f, 0.5f, 0.0f, //bod vpravo nahoře
	0.5f, -0.5f, 0.0f, //bod vpravo dole
   -0.5f, -0.5f, 0.0f,  //bod vlevo dole
    -0.5f, 0.5f, 0.0f //bod vlevo nahoře
};*/

//rovnostranny barevny
/*float points[] = {
	// positions         // colors
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};*/

float points[] = {
	// positions         // colors
	0.9f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	0.1f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	0.1f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};

float points2[] = {
	// positions         // colors
	0.7f, -0.6f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	0.3f, -0.6f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f
};

float points3[] = {
	// positions         // colors
	-0.9f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,   // bottom right
	-0.1f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom left
	-0.1f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f  // top
};

float points4[] = {
	// positions         // colors
	-1.4f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // bottom right
	-0.6f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom left
	-0.6f,  1.5f, 0.0f,  0.0f, 0.0f, 0.0f  // top
};

float polygon[] = {
	// positions         // colors
	-0.5f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f,   // Top-left
	0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Top-right
	0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // Bottom-right
	-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f // Bottom-left
};


/*const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);" 
"}";*/



///purple color
/*const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";*/


//yellow color
/*const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (1.0, 1.0, 0.0, 0.0);" //1.0f, 1.0f, 0.0f, 0.0f
"}";*/


//light blue color
const char* fragment_shaderxd =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.3, 0.3, 0.3, 0.0);" //0.0f, 1.0f, 1.0f, 1.0f --> svetle modrá
"}";

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

const char* vertex_shader2 =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 aColor;"
"out vec3 ourColor;"
"uniform mat4 transform;"
"void main () {"
"     gl_Position = transform * vec4 (vp, 1.0);"
"     ourColor = aColor;"
"}";


const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 ourColor;"
"void main () {"
"     frag_colour = vec4 (ourColor, 1.0);"
"}";

///fragment shader pro druhý trojuhelnik
const char* fragment_shader2 =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 ourColor;"
"void main () {"
"     frag_colour = vec4 (ourColor, 1.0);"
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
const char* vertex_shadercviko5=
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform mat3 normalMatrix; //(M-1)T"
"void main(void){"
"    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_Position,1.0f);"
"    ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);"
"    ex_worldNormal = normalMatrix * in_Normal; //příště"
"}";

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


int main()
{
	//rotace: 35, glm::vec3(0.0f, 0.0f, 1.0f) //vektor je okolo které osy to rotuje??
	//posun: sh , glm::vec3(0.0f, -0.5f, 0.0f)
	//zvetseni: sc, glm::vec3(0.3f)

	auto* application = new Application(800, 600, "ZPG");
    __attribute__((unused)) TransformationType sh = TransformationType::Shift;
    __attribute__((unused)) TransformationType sc = TransformationType::Scale;
	glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, 4.0f);
	//glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);

	application->createCamera(cameraEye, cameraDir);

    /*
    __attribute__((unused)) int obj1 = application->createNewObject(1, points2, sizeof(points2), 1, make_pair(0, 1), 3, 6 * sizeof(float), make_pair((void*) nullptr,
		(void*)(3 * sizeof(float))), vertex_shaderCamera, fragment_shader2, GL_TRIANGLES, 3);

	int obj2 = application->createNewObject(1, points3, sizeof(points3), 1, make_pair(0, 1), 3, 6 * sizeof(float),
		make_pair((void*) nullptr, (void*)(3 * sizeof(float))), vertex_shaderCamera, fragment_shader, GL_TRIANGLES, 3);

	application->transformObject(obj2, sh, glm::vec3(0.0f, -0.5f, 0.0f));
	application->transformObject(obj2, sc, glm::vec3(0.3f));

	int obj3 = application->createNewObject(1, polygon, sizeof(polygon), 1, make_pair(0, 1), 3, 6 * sizeof(float),
		make_pair((void*) nullptr, (void*)(3 * sizeof(float))), vertex_shaderCamera, fragment_shader, GL_POLYGON, 4);
	application->transformObject(obj3, sc, glm::vec3(0.3f));
	//application->transformObject(obj3, 90, glm::vec3(0.0f, 1.0f, 0.0f));
	application->transformObject(obj3, 180, glm::vec3(1.0f, 0.0f, 0.0f));
*/

	int sphere1 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderCamera, fragment_shaderxd, GL_TRIANGLES, 2904);

    application->transformObject(sphere1, sc, glm::vec3(0.3));
    application->transformObject(sphere1, sh, glm::vec3(-3.f, 0.0f, 0.0f));

    int sphere2 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderCamera, fragment_shaderxd, GL_TRIANGLES, 2904);

    application->transformObject(sphere2, sc, glm::vec3(0.3));
    application->transformObject(sphere2, sh, glm::vec3(3.f, 0.0f, 0.0f));


	int sphere3 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderCamera, fragment_shaderxd, GL_TRIANGLES, 2904);

    application->transformObject(sphere3, sc, glm::vec3(0.3));
    application->transformObject(sphere3, sh, glm::vec3(0.f, -3.0f, 0.0f));

    int sphere4 = application->createNewObject(1, const_cast<float *>(sphere), sizeof(sphere), 1, make_pair(0, 1), 3,
                                 6 * sizeof(float), make_pair((void*) nullptr,(void*)(3 * sizeof(float))),
                                 vertex_shaderCamera, fragment_shaderxd, GL_TRIANGLES, 2904);

    application->transformObject(sphere4, sc, glm::vec3(0.3));
    application->transformObject(sphere4, sh, glm::vec3(0.f, 3.0f, 0.0f));


    application->run();
	application->~Application();
	exit(EXIT_SUCCESS);
}
