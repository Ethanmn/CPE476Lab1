#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

const std::string kShaderPath = "../shaders/";

Shader::Shader(
      const std::string& name,
      const std::vector<Attribute>& attributes,
      const std::vector<Uniform>& uniforms) :
   gl_shader_(GLShader::compileAndLinkShader(kShaderPath + name + ".vert", kShaderPath + name + ".frag"))
{
   for (const auto& attr : attributes) {
      attribute_locations_.insert(std::make_pair(
               attr,
               gl_shader_.getAttributeLocation(attribute_name(attr))));
   }
   for (const auto& uniform : uniforms) {
      uniform_locations_.insert(std::make_pair(
               uniform,
               gl_shader_.getUniformLocation(uniform_name(uniform))));
   }
}

void Shader::use() {
   gl_shader_.use();
}

void Shader::drawMesh(const IndexBufferObject& index_buffer, const std::vector<ArrayBufferObject>& array_buffer_objects) {
   bindIndexBuffer(index_buffer);
   bindAndEnableAttributes(array_buffer_objects);
   glDrawElements(GL_TRIANGLES, index_buffer.size, GL_UNSIGNED_SHORT, 0);
   disableAttributes(array_buffer_objects);
}

void Shader::bindIndexBuffer(const IndexBufferObject& index_buffer) {
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.handle);
}

void Shader::bindAndEnableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects) {
   for (const auto& buffer_object : array_buffer_objects) {
      gl_shader_.bindAndEnableAttribute(buffer_object);
   }
}

void Shader::disableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects) {
   for (const auto& buffer_object : array_buffer_objects) {
      gl_shader_.disableAttribute(buffer_object);
   }
}
