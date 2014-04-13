#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

#include "gl_adapters/buffer_object.h"
#include "gl_adapters/gl_shader.h"
#include "gl_adapters/uniform_matrix.h"

struct Shader {
   Shader(
         const std::string& name,
         const std::vector<std::string>& attributes,
         const std::vector<std::string>& uniforms);

   void use();
   void drawMesh(
         const IndexBufferObject& index_buffer,
         const std::vector<ArrayBufferObject>& array_buffer_objects);

   // Helper method. Gets the shader handle and the attribute location of the
   // given attribute.
   std::pair<GLShaderHandle, GLAttributeLocation> attributeLocation(
         const std::string& attribute) {
      return std::make_pair(
            gl_shader_.program(),
            attribute_locations_.at(attribute));
   }
   // Helper method. Gets the shader handle and the uniform location of the
   // given uniform.
   std::pair<GLShaderHandle, GLUniformLocation> uniformLocation(
         const std::string& uniform) {
      return std::make_pair(
            gl_shader_.program(),
            uniform_locations_.at(uniform));
   }

   // Helper method. Gets all of the attributes from shaders and
   // forms a map for use in createArrayBuffer.
   static GLAttributeLocationMap getAttributes(
         const std::vector<std::pair<Shader&, std::string>>& desired_attributes);

   void uniformMatrix(const UniformMatrix& uniform) {
      uniform.sendToShader(gl_shader_);
   }

  private:
   void bindIndexBuffer(const IndexBufferObject& index_buffer);
   void bindAndEnableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects);
   void disableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects);

   GLShader gl_shader_;
   std::map<std::string, GLAttributeLocation> attribute_locations_;
   std::map<std::string, GLUniformLocation> uniform_locations_;
};

#endif // SHADER_H_
