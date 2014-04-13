#include "projection.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shaders.h"

namespace {
   glm::mat4 projectionMatrix() {
      const float field_of_view_y = 80.0f;
      const float z_near = 0.1f;
      const float z_far = 100.0f;
      const float aspect_ratio = 640.0f/480.0f;
      return glm::perspective(field_of_view_y, aspect_ratio, z_near, z_far);
   }
}

Projection::Projection(Shaders& shaders) :
   projection_matrix_(projectionMatrix()),
   projection_uniforms_(shaders.getUniforms("uProjectionMatrix")) {}

void Projection::sendToShader(Shader& shader) {
   shader.uniformMat4(projection_uniforms_, projection_matrix_);
}
