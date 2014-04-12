#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <GL/glew.h>

#include "gl_adapters/BufferObject.h"

struct GLShader {
   GLShader(GLuint linked_program) : program_(linked_program) {}

   void use();

   void bindIndexBuffer(const IndexBufferObject& index_buffer);
   void bindAndEnableAttribute(const ArrayBufferObject& array_buffer);
   void disableAttribute(const ArrayBufferObject& array_buffer);

   GLint getAttributeLocation(const std::string& attribute);
   GLint getUniformLocation(const std::string& uniform);

  private:
   GLuint program_;
};

#endif // GL_SHADER_H_
