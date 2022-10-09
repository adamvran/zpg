#include <cstdlib>
#include "Application.h"
#include "Shader.h"
//Include GLM
#include "lib/glm/glm/vec3.hpp" // glm::vec3
#include "lib/glm/glm/vec4.hpp" // glm::vec4
#include "lib/glm/glm/mat4x4.hpp" // glm::mat4
#include "lib/glm/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "lib/glm/glm/gtc/type_ptr.hpp" // glm::value_ptr

float triangle1[] = {
        // positions         // colors
        0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        0.1f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.1f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};

float triangle2[] = {
        // positions         // colors
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.1f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        -0.1f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};


const char* vertex_shader =
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

using namespace std;

int main()
{
    auto* application = new Application(800, 600, "ZPG");


    application->createNewObject(1, triangle1, sizeof(triangle1), 1, make_pair(0, 1), 3, 6 * sizeof(float), make_pair((void*) nullptr,
                                 (void*)(3 * sizeof(float))), vertex_shader, fragment_shader);

    application->createNewObject(1, triangle2, sizeof(triangle2), 1, make_pair(0, 1), 3, 6 * sizeof(float), make_pair((void*) nullptr,
                                 (void*)(3 * sizeof(float))), vertex_shader, fragment_shader);
    application->run(3); //num of vertexes
    application->~Application();
    exit(EXIT_SUCCESS);
}
