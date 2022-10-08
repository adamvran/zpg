#include <cstdlib>
#include "Application.h"
#include "Shader.h"

float points[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};

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

using namespace std;

int main()
{
    auto* application = new Application(800, 600, "ZPG");
    application->createNewObject(1, points, sizeof(points), 1, make_pair(0, 1), 3, 6 * sizeof(float), make_pair((void*) nullptr,
                                 (void*)(3 * sizeof(float))), vertex_shader, fragment_shader);
    application->run();
    application->~Application();
    exit(EXIT_SUCCESS);
}
