#include "mesh_loader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <iostream>

AssimpMesh loadMesh(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
    if (!scene) {
       std::cerr << "Failed to load: " << path << std::endl;
       exit(EXIT_FAILURE);
    }

    aiMesh *mesh = scene->mMeshes[0];
    AssimpMesh ret;
    float max_vert = 0.0f;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
       for (int j = 0; j < 3; ++j) {
          ret.vertex_array.push_back(mesh->mVertices[i][j]);
          max_vert = std::max(
                max_vert,
                std::abs(mesh->mVertices[i][j]));
       }
    }
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
       for (int j = 0; j < 3; ++j) {
          ret.vertex_array[i*3 + j] /= max_vert;
       }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
       ret.index_array.insert(
             ret.index_array.end(),
             mesh->mFaces[i].mIndices,
             mesh->mFaces[i].mIndices + sizeof(unsigned int) * 3);
    }

    return std::move(ret);
}
