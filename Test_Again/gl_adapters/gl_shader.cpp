#include "gl_shader.h"

#include "gl_adapters/buffer_object.h"

void GLShader::use() {
   glUseProgram(program_);
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
   return glGetAttribLocation(program_, attribute.c_str());
}

GLUniformLocation GLShader::getUniformLocation(const std::string& uniform) {
   return glGetAttribLocation(program_, uniform.c_str());
}
