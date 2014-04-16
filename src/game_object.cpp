#include "game_object.h"

#include <glm/gtc/matrix_transform.hpp>
#include "graphics/Shader.h"

GameObject::GameObject(
      const Bounds& x_bounds,
      const Bounds& z_bounds,
      const Mesh& mesh,
      Shaders& shaders) :
   center_(x_bounds.randomInclusive(), kRadius, z_bounds.randomInclusive()),
   velocity_(0, 1, 0),
   mesh_(mesh),
   model_matrix_(shaders, glm::mat4())
   {}

void GameObject::step(units::MS dt) {
   center_ += velocity_ * static_cast<float>(dt);
}

void GameObject::draw(Shader& shader, const glm::mat4& view) {
   model_matrix_.model_matrix = glm::translate(glm::mat4(), center_);
   shader.drawMesh(model_matrix_.calculateAffineUniforms(view), mesh_);
}
