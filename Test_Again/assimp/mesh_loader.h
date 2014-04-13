#ifndef MESH_LOADER_H_
#define MESH_LOADER_H_

#include <string>

struct aiScene;

struct AssimpMesh {
   float* vertexArray;
   float* normalArray;
   float* uvArray;
   unsigned int* indexArray;

   int numVerts;
};

class MeshLoader {
   AssimpMesh getModel(const aiScene* scene);
  public:
   bool importModel(const std::string& pFile);

   AssimpMesh model;
};

#endif // MESH_LOADER_H_
