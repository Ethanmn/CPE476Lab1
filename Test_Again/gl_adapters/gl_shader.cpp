#include "gl_shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "gl_adapters/buffer_object.h"

namespace {
   void uniformMatrix4fv(GLint location, const GLfloat *value) {
      glUniformMatrix4fv(location, 1, GL_FALSE, value);
   }
}

void GLShader::use() {
   glUseProgram(program_);
}

void GLShader::uniformMat4(
      const GLUniformLocationMap& uniforms,
      const glm::mat4& data) {
   uniformMatrix4fv(uniforms.at(program_), glm::value_ptr(data));
}

void GLShader::bindAndEnableAttribute(const ArrayBufferObject& array_buffer) {
   glBindBuffer(GL_ARRAY_BUFFER, array_buffer.handle);
   glVertexAttribPointer(
         array_buffer.attribute_locations.at(program_),
         array_buffer.num_components,
         GL_FLOAT, GL_FALSE,
         0,
         nullptr);
   glEnableVertexAttribArray(array_buffer.attribute_locations.at(program_));
}

void GLShader::disableAttribute(const ArrayBufferObject& array_buffer) {
   glDisableVertexAttribArray(array_buffer.attribute_locations.at(program_));
}

GLAttributeLocation GLShader::getAttributeLocation(const std::string& attribute) {
   GLint a = glGetAttribLocation(program_, attribute.c_str());
   if (a < 0) {
      std::cout << "Could not find attribute location for: " << attribute << " in program: " << program_ << std::endl;
      exit(EXIT_FAILURE);
   }
   return GLAttributeLocation(a);
}

GLUniformLocation GLShader::getUniformLocation(const std::string& uniform) {
   GLint u = glGetUniformLocation(program_, uniform.c_str());
   if (u < 0) {
      std::cout << "Could not find uniform location for: " << uniform << " in program: " << program_ << std::endl;
      exit(EXIT_FAILURE);
   }
   return GLUniformLocation(u);
}
