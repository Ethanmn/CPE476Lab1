#include "GroundPlane.h"

#include "Shader.h"
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

GroundPlane::GroundPlane(Shaders& shaders) :
   vertex_buffer_object_(
         createArrayBufferObject(
            ground_vertices,
            shaders.getAttributes("aPosition"),
            3)),
   index_buffer_object_(createIndexBufferObject(ground_indices))
{
}

void GroundPlane::draw(Shader& shader) {
   shader.drawMesh(index_buffer_object_, {vertex_buffer_object_});
}
