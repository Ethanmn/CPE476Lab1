#ifndef GROUND_PLANE_H_
#define GROUND_PLANE_H_

#include "BufferObject.h"

struct Shaders;

struct GroundPlane {
   GroundPlane();

   void draw(Shaders& shaders);

  private:
   ArrayBufferObject vertex_buffer_object_;
   IndexBufferObject index_buffer_object_;
};

#endif // GROUND_PLANE_H_
