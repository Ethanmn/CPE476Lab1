#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "graphics/gl_adapters/uniform_matrix.h"
#include "graphics/mesh.h"
#include "graphics/model_view_uniform_matrix.h"

struct Shader;
struct Shaders;

struct GroundPlane {
   GroundPlane(Shaders& shaders);

   void draw(Shader& shader, const glm::mat4& view);

  private:
   Mesh mesh_;
   ModelViewUniformMatrix model_matrix_;
};

#endif // GROUND_PLANE_H_
