#pragma once
#include <string>
#include "ShaderLoader.h"

class Loader {
public:
    Loader();
    ~Loader();
    std::string load(const char *path);
};
