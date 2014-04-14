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

    aiMesh& mesh = *scene->mMeshes[0];
    AssimpMesh ret;
    ret.vertex_array.insert(
          ret.vertex_array.begin(),
          (float*)(mesh.mVertices),
          (float*)(mesh.mVertices) + mesh.mNumFaces * sizeof(unsigned int) * 3);

    ret.normal_array.insert(
          ret.normal_array.begin(),
          (float*)(mesh.mNormals),
          (float*)(mesh.mNormals) + mesh.mNumFaces * sizeof(unsigned int) * 3);

    for (unsigned int i = 0; i < mesh.mNumFaces; ++i) {
       ret.index_array.insert(
             ret.index_array.end(),
             mesh.mFaces[i].mIndices,
             mesh.mFaces[i].mIndices + sizeof(unsigned int) * 3);
    }

    return std::move(ret);
}
