#include "DrawMesh.h"

void drawMesh(
      Shaders& shaders,
      ShaderType shader_type,
      const IndexBufferObject& index_buffer_object,
      const std::vector<ArrayBufferObject>& array_buffer_objects) {
   Shader& shader = shaders.use(shader_type);
   shader.bindIndexBuffer(index_buffer_object);
   shader.bindAndEnableAttributes(array_buffer_objects);

   glDrawElements(GL_TRIANGLES, index_buffer_object.size, GL_UNSIGNED_SHORT, 0);

   for (const auto& abo : array_buffer_objects) {
      shader.disableAttribute(abo.attribute);
   }
   shaders.clear();
}
