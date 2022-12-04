#include "LoaderObject.h"

void LoaderObject::setImportOptions()
{
    this->importOptions = aiProcess_Triangulate
                          | aiProcess_OptimizeMeshes              // slou�en� mal�ch plo�ek
                          | aiProcess_JoinIdenticalVertices       // NUTN� jinak hodn� duplikuje
                          | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
                          | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
}

void LoaderObject::setScene(const char* path)
{
    this->scene = this->importer.ReadFile(path, this->importOptions);
}

LoaderObject::LoaderObject(const char* path)
{
    this->count = 0;
    this->setImportOptions();
    this->setScene(path);
}

std::pair<int, std::vector<float>> LoaderObject::initData()
{
    std::vector<float> data;
    if (this->scene) {
        aiMesh* mesh = this->scene->mMeshes[0];
        this->count = mesh->mNumFaces * 3;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            for (unsigned int j = 0; j < 3; j++)
            {
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
            }
        }
    }
    return { this->count, data };
}
