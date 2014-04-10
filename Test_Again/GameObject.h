/*#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

typedef struct
{
    float *vertexArray;
    float *normalArray;
    float *uvArray;

    int numVerts;
} Model;

class GameObject {
    Model model;

private:
    Model GameObject::getModel(const aiScene* scene);
public:
    bool importModel(const std::string& pFile);
};

#endif //GAMEOBJECT_H_*/