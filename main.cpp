#include <cstdlib>
#include "Application.h"
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

int main()
{
    auto* app = new Application(800,600);
    //(countVBO,countVAO,size,index, points, enable vertex array, sizeof(points), GLsizei stride, GLvoid* pointer)
    app->createVertexObject(1, 1, 3, 0, points, 0, sizeof(points), 6 * sizeof (float), (void*)nullptr);
    app->createVertexObject(1, 1, 3, 1, points, 1, sizeof(points), 6 * sizeof (float), (void*)(3 * sizeof(float)));
    app->createShader(GL_VERTEX_SHADER, vertex_shader);
    app->createShader(GL_FRAGMENT_SHADER, fragment_shader);

    app->run();
    app->~Application();

    exit(EXIT_SUCCESS);
}
