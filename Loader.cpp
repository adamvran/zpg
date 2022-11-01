#include <fstream>
#include "Loader.h"

Loader::Loader() = default;

Loader::~Loader() = default;

std::string Loader::load(const char* path)
{
    std::ifstream file_open;
    file_open.open(path);
    if (!file_open.is_open())
    {
        std::cout << "File can not be opened: " << path << std::endl;
        exit(1);
    }
    std::string result;
    std::ostringstream tmp;
    tmp << file_open.rdbuf();
    result = tmp.str();
    file_open.close();
    return result;
}
