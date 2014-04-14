#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "mesh.h"

const std::string kShaderPath = "../shaders/";

Shader::Shader(
      const std::string& name,
      const std::vector<Attribute>& attributes,
      const std::vector<Uniform>& uniforms) :
   gl_shader_(GLShader::compileAndLinkShader(kShaderPath + name + ".vert", kShaderPath + name + ".frag")),
   program_name_(name)
{
   std::cout << "Successfully compiled/linked shader: "
      << name
      << " as program: "
      << gl_shader_.program()
      << std::endl;
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

void Shader::drawMesh(const Mesh& mesh) {
   bindIndexBuffer(mesh.index_buffer_object);
   bindAndEnableAttributes(mesh.attribute_buffer_objects);
   glDrawElements(GL_TRIANGLES, mesh.index_buffer_object.size, GL_UNSIGNED_SHORT, 0);
   disableAttributes(mesh.attribute_buffer_objects);
}

std::pair<GLShaderHandle, GLAttributeLocation> Shader::attributeLocation(
      const Attribute& attribute) {
   if (attribute_locations_.count(attribute) == 0) {
      std::cerr << "Could not find attribute: " << attribute_name(attribute) <<
         " in shader program: " << program_name_ << std::endl;
      std::cerr << "Make sure you add it to the list of attributes" << std::endl;
      exit(EXIT_FAILURE);
   }
   return std::make_pair(
         gl_shader_.program(),
         attribute_locations_.at(attribute));
}

std::pair<GLShaderHandle, GLUniformLocation> Shader::uniformLocation(
      const Uniform& uniform) {
   if (uniform_locations_.count(uniform) == 0) {
      std::cerr << "Could not find uniform: " << uniform_name(uniform) <<
         " in shader program: " << program_name_ << std::endl;
      std::cerr << "Make sure you add it to the list of uniforms" << std::endl;
      exit(EXIT_FAILURE);
   }
   return std::make_pair(
         gl_shader_.program(),
         uniform_locations_.at(uniform));
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
