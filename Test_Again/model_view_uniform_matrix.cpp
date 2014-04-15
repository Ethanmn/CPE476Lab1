#include "model_view_uniform_matrix.h"

#include "Shaders.h"

ModelViewUniformMatrix::ModelViewUniformMatrix(Shaders& shaders, const glm::mat4& model_matrix) :
   model_matrix(model_matrix),
   model_view_uniforms_(shaders.getUniforms(Uniform::MODEL_VIEW)),
   normal_uniforms_(shaders.getUniforms(Uniform::NORMAL)) {}

AffineUniforms
ModelViewUniformMatrix::calculateAffineUniforms(const glm::mat4& view_matrix) const {
   const glm::mat4 model_view = view_matrix * model_matrix;
   const glm::mat4 normal = glm::transpose(glm::inverse(model_view));
   return {
      UniformMatrix(model_view, model_view_uniforms_),
      UniformMatrix(normal, normal_uniforms_),
   };
}
