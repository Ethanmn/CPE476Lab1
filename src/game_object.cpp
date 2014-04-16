#include "game_object.h"

#include <glm/gtc/matrix_transform.hpp>
#include "graphics/uniforms.h"
#include "graphics/Shader.h"
#include "graphics/Shaders.h"

GameObject::GameObject(
      const GroundPlane& ground_plane,
      const Mesh& mesh,
      Shaders& shaders) :
   should_move_(true),
   should_blue_(false),
   center_(
         ground_plane.x_bounds().shrink(2*kRadius).randomInclusive(),
         kRadius,
         ground_plane.z_bounds().shrink(2*kRadius).randomInclusive()),
   velocity_(0.005f * cos(rand()), 0, 0.005f * sin(rand())),
   blue_uniform_(shaders.getUniforms(Uniform::BLUE)),
   mesh_(mesh),
   model_matrix_(shaders, glm::mat4()) {}

void GameObject::step(units::MS dt, const GroundPlane& ground_plane, std::vector<GameObject>& game_objects) {
   if (!should_move_) return;
   const glm::vec3 delta = velocity_ * static_cast<float>(dt);
   const glm::vec3 new_center = center_ + delta;
   if (Bounds(new_center.x - kRadius,
              new_center.x + kRadius).within(ground_plane.x_bounds()) &&
       Bounds(new_center.z - kRadius,
              new_center.z + kRadius).within(ground_plane.z_bounds())) {
      bool collided = false;
      for (auto& g : game_objects) {
         if (this != &g && BoundingSphere{new_center, kRadius}.collides(g.bounding_sphere())) {
            onCollision();
            g.onCollision();
            collided = true;
         }
      }
      if (!collided)
         center_ = new_center;
   } else {
      velocity_ = -velocity_;
      step(dt, ground_plane, game_objects);
   }
}

void GameObject::draw(Shader& shader, const glm::mat4& view) {
   shader.uniformFloat(blue_uniform_, should_blue_ ? 1.0f : 0.0f);
   model_matrix_.model_matrix = glm::translate(glm::mat4(), center_);
   shader.drawMesh(model_matrix_.calculateAffineUniforms(view), mesh_);
}
