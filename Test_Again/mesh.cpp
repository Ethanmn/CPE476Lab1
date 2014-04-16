#include "mesh.h"

#include "graphics/assimp/mesh_loader.h"
#include "Shaders.h"

//static
Mesh Mesh::fromAssimpMesh(Shaders& shaders, const AssimpMesh& mesh) {
   return {
      createIndexBufferObject(mesh.index_array),
      {
         createArrayBufferObject(
            mesh.vertex_array,
            shaders.getAttributes(Attribute::VERTEX),
            3),
         createArrayBufferObject(
            mesh.normal_array,
            shaders.getAttributes(Attribute::NORMAL),
            3),
      }
   };
}
