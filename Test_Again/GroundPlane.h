#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "mesh.h"
#include "model_normal_uniform_matrix.h"

struct Shader;
struct Shaders;

struct GroundPlane {
   GroundPlane(Shaders& shaders);

   void draw(Shader& shader);

  private:
   Mesh mesh_;
   ModelNormalUniformMatrix model_normal_uniform_;
};

#endif // GROUND_PLANE_H_
