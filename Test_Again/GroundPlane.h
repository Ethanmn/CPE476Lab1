#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "gl_adapters/buffer_object.h"
#include "gl_adapters/uniform_matrix.h"
#include "mesh.h"

struct Shader;
struct Shaders;

struct GroundPlane {
   GroundPlane(Shaders& shaders);

   void draw(Shader& shader);

  private:
   Mesh mesh_;
   UniformMatrix model_matrix_;
};

#endif // GROUND_PLANE_H_
