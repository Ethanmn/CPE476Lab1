#include "DrawMesh.h"

void drawMesh(
      Shader& shader,
      const IndexBufferObject& index_buffer_object,
      const std::vector<ArrayBufferObject>& array_buffer_objects) {
   shader.bindIndexBuffer(index_buffer_object);
   shader.bindAndEnableAttributes(array_buffer_objects);
   glDrawElements(GL_TRIANGLES, index_buffer_object.size, GL_UNSIGNED_SHORT, 0);
   shader.disableAttributes(array_buffer_objects);
}
