#include "mesh_loader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

AssimpMesh MeshLoader::getModel(const aiScene* scene)
{
    aiMesh *mesh = scene->mMeshes[0];
    AssimpMesh retModel;

    retModel.numVerts = mesh->mNumFaces*3;
    retModel.vertexArray = new float[mesh->mNumFaces*3*3];
    retModel.normalArray = new float[mesh->mNumFaces*3*3];
    retModel.uvArray = new float[mesh->mNumFaces*3*2];
    retModel.indexArray = new unsigned int[retModel.numVerts];

    float max_vert = 0.0f;
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        for(int j = 0; j < 3; j++)
        {
           memcpy(retModel.indexArray, face.mIndices, sizeof(unsigned int) * 3);
           retModel.indexArray += 3;

           aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
           memcpy(retModel.uvArray, &uv, sizeof(float) * 2);
           retModel.uvArray += 2;

           aiVector3D normal = mesh->mNormals[face.mIndices[j]];
           memcpy(retModel.normalArray, &normal, sizeof(float) * 3);
           retModel.normalArray += 3;

           aiVector3D pos = mesh->mVertices[face.mIndices[j]];
           memcpy(retModel.vertexArray, &pos, sizeof(float) * 3);
           retModel.vertexArray += 3;
           for (int i = 0; i < 3; ++i) {
              max_vert = std::max(
                    std::abs(mesh->mVertices[face.mIndices[j]][i]),
                    max_vert
                    );
           }
        }
    }

    retModel.uvArray -= mesh->mNumFaces * 3 * 2;
    retModel.normalArray -= mesh->mNumFaces * 3 * 3;
    retModel.vertexArray -= mesh->mNumFaces * 3 * 3;
    retModel.indexArray -= mesh->mNumFaces * 3;
    for (size_t i = 0; i < mesh->mNumFaces * 3 * 3; ++i) {
       retModel.vertexArray[i] /= max_vert;
       printf("%f, ", retModel.vertexArray[i]);
    }
    printf("\n");

    return retModel;
}

bool MeshLoader::importModel(const std::string& pFile)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // propably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (!scene)
    {
        //DoTheErrorLogging(importer.GetErrorString());
        return false;
    }
    // Now we can access the file's contents.
    model = getModel(scene);

    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}
