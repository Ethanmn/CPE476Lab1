#include "gl_shader.h"

void GLShader::use() {
   glUseProgram(program_);
}

void GLShader::bindIndexBuffer(const IndexBufferObject& index_buffer) {
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.handle);
}

void GLShader::bindAndEnableAttribute(const ArrayBufferObject& array_buffer) {
   glBindBuffer(GL_ARRAY_BUFFER, array_buffer.handle);
   glVertexAttribPointer(
         array_buffer.attribute_location,
         array_buffer.num_components,
         GL_FLOAT, GL_FALSE,
         0,
         nullptr);
   glEnableVertexAttribArray(array_buffer.attribute_location);
}

void GLShader::disableAttribute(const ArrayBufferObject& array_buffer) {
   glDisableVertexAttribArray(array_buffer.attribute_location);
}

GLint GLShader::getAttributeLocation(const std::string& attribute) {
   return glGetAttribLocation(program_, attribute.c_str());
}

GLint GLShader::getUniformLocation(const std::string& uniform) {
   return glGetAttribLocation(program_, uniform.c_str());
}
