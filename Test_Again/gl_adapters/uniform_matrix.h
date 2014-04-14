#ifndef UNIFORM_MATRIX_H_
#define UNIFORM_MATRIX_H_

#include <glm/glm.hpp>

#include "gl_adapters/gl_types.h"

struct GLShader;

struct UniformMatrix {
   UniformMatrix(
         const glm::mat4& matrix,
         const GLUniformLocationMap& uniforms) :
      matrix(matrix),
      uniforms_(uniforms) {}

   void sendToShader(GLShader& shader) const;
   glm::mat4 matrix;

  private:
   GLUniformLocationMap uniforms_;
};

#endif // UNIFORM_MATRIX_H_
