#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
/*
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
*/
struct Vector3
{
    float x;
    float y;
    float z;
};

class GameObject {
    //Model model;

private:
    Vector3 position;
    Vector3 direction;
    float velocity;
    Vector3 center;
    float radius;
    //Model GameObject::getModel(const aiScene* scene);
public:
    GameObject();
    ~GameObject();

    //bool importModel(const std::string& pFile);
};

#endif //GAMEOBJECT_H_