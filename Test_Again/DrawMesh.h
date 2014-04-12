#ifndef DRAW_MESH_H_
#define DRAW_MESH_H_

#include "gl_adapters/BufferObject.h"
#include "Shader.h"

void drawMesh(
      Shader& shader,
      const IndexBufferObject& index_buffer_object,
      const std::vector<ArrayBufferObject>& array_buffer_objects);

#endif // DRAW_MESH_H_
