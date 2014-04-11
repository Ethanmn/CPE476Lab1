#include "GroundPlane.h"

#include "DrawMesh.h"
#include "Shaders.h"

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
   0.5, 0.5, 0.0,
};

const std::vector<unsigned short> ground_indices{
   0, 1, 2, 3, 1, 2
};

GroundPlane::GroundPlane() :
   vertex_buffer_object_(createArrayBufferObject(ground_vertices, "aPosition", 3)),
   index_buffer_object_(createIndexBufferObject(ground_indices))
{
}

void GroundPlane::draw(Shaders& shaders) {
   drawMesh(
         shaders,
         ShaderType::GROUND,
         index_buffer_object_,
         {vertex_buffer_object_});
}
