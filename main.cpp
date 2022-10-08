//Include GLEW
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
/*
//Include GLM
#include "lib/glm/glm/vec3.hpp" // glm::vec3
#include "lib/glm/glm/vec4.hpp" // glm::vec4
#include "lib/glm/glm/mat4x4.hpp" // glm::mat4
#include "lib/glm/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "lib/glm/glm/gtc/type_ptr.hpp" // glm::value_ptr
*/
//Include the standard C++ headers
#include <cstdlib>
#include <cstdio>
#include "Application.h"
#include "Shader.h"

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

float points[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
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

/*
* //light blue color
const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 1.0, 1.0, 1.0);" //0.0f, 1.0f, 1.0f, 1.0f --> svetle modrá
"}";*/


const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "layout(location=1) in vec3 aColor;"
        "out vec3 ourColor;"
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);"
        "     ourColor = aColor;"
        "}";

const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "in vec3 ourColor;"
        "void main () {"
        "     frag_colour = vec4 (ourColor, 1.0);"
        "}";

/*
//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
        glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
*/
using namespace std;

int main(void)
{
    Application* application = new Application(800, 600, "ZPG Ocelkova - cv.2");
    application->createNewObject(1, points, sizeof(points), 1, make_pair(0, 1), make_pair(3, 3), make_pair(6 * sizeof(float),
                                                                                                           6 * sizeof(float)), make_pair((void*) nullptr, (void*)(3 * sizeof(float))), vertex_shader, fragment_shader);
    application->run();
    application->~Application();
    exit(EXIT_SUCCESS);
}
