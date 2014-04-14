#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "gl_adapters/buffer_object.h"

struct Shader;
struct Shaders;

struct GroundPlane {
   GroundPlane(Shaders& shaders);

   void draw(Shader& shader);

  private:
   ArrayBufferObject vertex_buffer_object_;
   IndexBufferObject index_buffer_object_;
};

#endif // GROUND_PLANE_H_
