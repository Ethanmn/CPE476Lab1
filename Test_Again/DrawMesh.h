#ifndef DRAW_MESH_H_
#define DRAW_MESH_H_

#include "BufferObject.h"
#include "Shaders.h"

void drawMesh(
      Shaders& shaders,
      ShaderType shader_type,
      const IndexBufferObject& index_buffer_object,
      const std::vector<ArrayBufferObject>& array_buffer_objects);

#endif // DRAW_MESH_H_
