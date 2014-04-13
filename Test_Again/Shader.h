#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

#include "gl_adapters/buffer_object.h"
#include "gl_adapters/gl_shader.h"

struct Shader {
   Shader(
         const std::string& name,
         const std::vector<std::string>& attributes,
         const std::vector<std::string>& uniforms);

   void use();
   void drawMesh(
         const IndexBufferObject& index_buffer,
         const std::vector<ArrayBufferObject>& array_buffer_objects);

   std::pair<GLShaderHandle, GLAttributeLocation> attributeLocation(
         const std::string& attribute) {
      return std::make_pair(
            gl_shader_.program(),
            attribute_locations_.at(attribute));
   }

   static std::map<GLShaderHandle, GLAttributeLocation> getAttributes(
         const std::vector<std::pair<Shader&, std::string>>& desired_attributes);

  private:
   void bindIndexBuffer(const IndexBufferObject& index_buffer);
   void bindAndEnableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects);
   void disableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects);

   GLShader gl_shader_;
   std::map<std::string, GLAttributeLocation> attribute_locations_;
   std::map<std::string, GLUniformLocation> uniform_locations_;
};

#endif // SHADER_H_
