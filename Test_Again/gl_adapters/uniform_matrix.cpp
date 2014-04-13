#include "gl_adapters/uniform_matrix.h"

#include "gl_adapters/gl_shader.h"

void UniformMatrix::sendToShader(GLShader& shader) {
   shader.uniformMat4(uniforms_, matrix_);
}
