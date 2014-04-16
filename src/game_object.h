#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>

#include "bounds.h"
#include "bounding_sphere.h"
#include "units.h"

#include "graphics/mesh.h"
#include "graphics/model_view_uniform_matrix.h"

struct Shader;

struct GameObject {
   GameObject(
         const Bounds& x_bounds,
         const Bounds& z_bounds,
         const Mesh& mesh,
         Shaders& shaders);

   void step(units::MS dt);
   void draw(Shader& shader, const glm::mat4& view);

   BoundingSphere bounding_sphere() const { return { center_, kRadius}; }

  private:
   const float kRadius = 1.0f;
   glm::vec3 center_;
   glm::vec3 velocity_;

   Mesh mesh_;
   ModelViewUniformMatrix model_matrix_;
};

#endif // GAME_OBJECT_H_
