/*#include "GameObject.h"

Model GameObject::getModel(const aiScene* scene)
{
    aiMesh *mesh = scene->mMeshes[0];
    Model retModel;

    retModel.numVerts = mesh->mNumFaces*3;
    retModel.vertexArray = new float[mesh->mNumFaces*3*3];
    retModel.normalArray = new float[mesh->mNumFaces*3*3];
    retModel.uvArray = new float[mesh->mNumFaces*3*2];

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        for(int j = 0; j < 3; j++)
        {
            aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
            memcpy(retModel.uvArray, &uv, sizeof(float) * 2);
            retModel.uvArray += 2;

            aiVector3D normal = mesh->mNormals[face.mIndices[j]];
            memcpy(retModel.normalArray, &normal, sizeof(float) * 3);
            retModel.normalArray += 3;

            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            memcpy(retModel.vertexArray, &pos, sizeof(float) * 3);
            retModel.vertexArray += 3;
        }
    }

    retModel.uvArray -= mesh->mNumFaces * 3 * 2;
    retModel.normalArray -= mesh->mNumFaces * 3 * 3;
    retModel.vertexArray -= mesh->mNumFaces * 3 * 3;

    return retModel;
}

bool GameObject::importModel(const std::string& pFile)
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
    GameObject::model = getModel(scene);

    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}*/