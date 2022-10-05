#pragma once
#include <cstdio>

class Callback
{
public:
    static void errorCallback(int error, const char* description);
};
