#pragma once
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
class Loader {
public:
    Loader();
    ~Loader();
    std::string load(const char *path);
};
