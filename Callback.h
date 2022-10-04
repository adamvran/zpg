#pragma once
#include "lib/glew/2.2.0_1/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include <cstdlib>
#include <cstdio>

class Callback
{
public:
    static void errorCallback(int error, const char* description);
};
