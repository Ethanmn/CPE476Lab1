#include "GroundPlane.h"

#include "Shader.h"

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
   0.5, 0.5, 0.0,
};

const std::vector<unsigned short> ground_indices{
   0, 1, 2, 3, 1, 2
};

GroundPlane::GroundPlane(Shader& shader) :
   shader_(shader),
   vertex_buffer_object_(shader.createArrayBufferObject(ground_vertices, "aPosition", 3)),
   index_buffer_object_(createIndexBufferObject(ground_indices))
{
}

void GroundPlane::draw() {
   shader_.drawMesh(index_buffer_object_, {vertex_buffer_object_});
}
