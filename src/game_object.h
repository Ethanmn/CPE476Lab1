#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#include <iostream>

#include "bounding_sphere.h"
#include "GroundPlane.h"
#include "units.h"

#include "graphics/mesh.h"
#include "graphics/model_view_uniform_matrix.h"
#include "graphics/gl_adapters/gl_types.h"

struct Shader;

struct GameObject {
   GameObject(
         const GroundPlane& ground_plane,
         const Mesh& mesh,
         Shaders& shaders);

   void step(units::MS dt, const GroundPlane& ground_plane, std::vector<GameObject>& game_objects);
   void draw(Shader& shader, const glm::mat4& view);

   BoundingSphere bounding_sphere() const { return { center_, kRadius}; }
   void onCollision() { should_blue_ = true; velocity_ = - velocity_; }

   void onCameraCollision() { should_move_ = false; }

  private:
   const float kRadius = 1.0f;
   bool should_move_;
   bool should_blue_;
   glm::vec3 center_;
   glm::vec3 velocity_;
   GLUniformLocationMap blue_uniform_; // violation of layering. but fuck it

   Mesh mesh_;
   ModelViewUniformMatrix model_matrix_;
};

#endif // GAME_OBJECT_H_
