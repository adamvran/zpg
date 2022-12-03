#pragma once
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include <vector>
#include <iostream>

class LoaderObject
{
private:
    unsigned int count;
    Assimp::Importer importer;
    unsigned int importOptions{};
    const aiScene* scene{};
    void setImportOptions();
    void setScene(const char* path);
public:
    explicit LoaderObject(const char* path);
    std::pair<int, std::vector<float>> initData();

};
