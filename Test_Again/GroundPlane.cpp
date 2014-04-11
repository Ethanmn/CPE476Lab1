#include "GroundPlane.h"

#include "Shaders.h"

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,

   0.5, 0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
};

GroundPlane::GroundPlane() :
   vertex_buffer_object_(createArrayBufferObject(ground_vertices, "aPosition", 3))
{
}

void GroundPlane::draw(Shaders& shaders) {
   Shader& shader = shaders.use(ShaderType::GROUND);
   shader.bindAndEnableAttributes({vertex_buffer_object_});

   glDrawArrays(GL_TRIANGLES, 0, 6);

   shader.disableAttribute("aPosition");
   shaders.clear();
}
