#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "gl_adapters/buffer_object.h"

struct Shader;

struct GroundPlane {
   GroundPlane(Shader& shader);

   void draw();

  private:
   Shader& shader_;
   ArrayBufferObject vertex_buffer_object_;
   IndexBufferObject index_buffer_object_;
};

#endif // GROUND_PLANE_H_
