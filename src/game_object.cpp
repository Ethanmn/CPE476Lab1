#include "game_object.h"

#include <glm/gtc/matrix_transform.hpp>
#include "graphics/Shader.h"

GameObject::GameObject(
      const GroundPlane& ground_plane,
      const Mesh& mesh,
      Shaders& shaders) :
   center_(
         ground_plane.x_bounds().shrink(2*kRadius).randomInclusive(),
         kRadius,
         ground_plane.z_bounds().shrink(2*kRadius).randomInclusive()),
   velocity_(0.005f, 0, 0.005f),
   mesh_(mesh),
   model_matrix_(shaders, glm::mat4())
   {}

void GameObject::step(units::MS dt, const GroundPlane& ground_plane) {
   if (!should_move_) return;
   const glm::vec3 delta = velocity_ * static_cast<float>(dt);
   const glm::vec3 new_center = center_ + delta;
   if (Bounds(new_center.x - kRadius,
              new_center.x + kRadius).within(ground_plane.x_bounds()) &&
       Bounds(new_center.z - kRadius,
              new_center.z + kRadius).within(ground_plane.z_bounds())) {
      center_ = new_center;
   } else {
      velocity_ = -velocity_;
      step(dt, ground_plane);
   }
}

void GameObject::draw(Shader& shader, const glm::mat4& view) {
   model_matrix_.model_matrix = glm::translate(glm::mat4(), center_);
   shader.drawMesh(model_matrix_.calculateAffineUniforms(view), mesh_);
}
