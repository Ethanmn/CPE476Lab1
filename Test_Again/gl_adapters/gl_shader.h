#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <string>

#include "gl_adapters/gl_types.h"

struct ArrayBufferObject;
struct IndexBufferObject;

struct GLShader {
   GLShader(GLShaderHandle linked_program) : program_(linked_program) {}

   void use();

   void bindAndEnableAttribute(const ArrayBufferObject& array_buffer);
   void disableAttribute(const ArrayBufferObject& array_buffer);

   GLAttributeLocation getAttributeLocation(const std::string& attribute);
   GLint getUniformLocation(const std::string& uniform);

   GLShaderHandle program() { return program_; }

  private:
   GLShaderHandle program_;
};

#endif // GL_SHADER_H_
