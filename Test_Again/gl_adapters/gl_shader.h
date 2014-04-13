#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <GL/glew.h>
#include <string>

struct ArrayBufferObject;
struct IndexBufferObject;

typedef GLuint GLShaderHandle;

struct GLShader {
   GLShader(GLShaderHandle linked_program) : program_(linked_program) {}

   void use();

   void bindIndexBuffer(const IndexBufferObject& index_buffer);
   void bindAndEnableAttribute(const ArrayBufferObject& array_buffer);
   void disableAttribute(const ArrayBufferObject& array_buffer);

   GLint getAttributeLocation(const std::string& attribute);
   GLint getUniformLocation(const std::string& uniform);

   GLShaderHandle program() { return program_; }

  private:
   GLShaderHandle program_;
};

#endif // GL_SHADER_H_
