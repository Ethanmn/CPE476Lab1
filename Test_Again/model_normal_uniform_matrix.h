#ifndef MODEL_NORMAL_UNIFORM_MATRIX_H_
#define MODEL_NORMAL_UNIFORM_MATRIX_H_

#include "gl_adapters/uniform_matrix.h"
#include "Shaders.h"

struct ModelNormalUniformMatrix {
   ModelNormalUniformMatrix(
         Shaders& shaders,
         const glm::mat4& model_matrix) :
      model_matrix(model_matrix),
      model_uniforms_(shaders.getUniforms(Uniform::MODEL)),
      normal_uniforms_(shaders.getUniforms(Uniform::NORMAL))
   {}

   glm::mat4 model_matrix;
   UniformMatrix model() const { return UniformMatrix(model_matrix, model_uniforms_); }
   UniformMatrix normal() const {
      return UniformMatrix(glm::transpose(glm::inverse(model_matrix)), normal_uniforms_);
   }

  private:
   GLUniformLocationMap model_uniforms_, normal_uniforms_;
};

#endif // MODEL_NORMAL_UNIFORM_MATRIX_H_
