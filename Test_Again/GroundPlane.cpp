#include "GroundPlane.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Shaders.h"

const std::vector<float> ground_vertices{
   -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   -0.5, 0.5, 0.0,
   0.5, 0.5, 0.0,
};
const std::vector<float> ground_normals{
   0, 0, 1,
   0, 0, 1,
   0, 0, 1,
   0, 0, 1,
};

const std::vector<unsigned short> ground_indices{
   0, 2, 1, 3, 1, 2
};

GroundPlane::GroundPlane(Shaders& shaders) :
   mesh_{
      createIndexBufferObject(ground_indices),
      {
         createArrayBufferObject(
            ground_vertices,
            shaders.getAttributes(Attribute::VERTEX),
            3),
         createArrayBufferObject(
            ground_normals,
            shaders.getAttributes(Attribute::NORMAL),
            3),
      }
   },
   model_matrix_(shaders,
         glm::rotate(glm::scale(glm::mat4(), glm::vec3(20.0f)), 90.0f, glm::vec3(1, 0, 0)))
{
}

void GroundPlane::draw(Shader& shader, const glm::mat4& view) {
   shader.drawMesh(model_matrix_.calculateAffineUniforms(view), mesh_);
}
