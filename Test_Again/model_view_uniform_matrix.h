#ifndef MODEL_VIEW_UNIFORM_MATRIX_H_
#define MODEL_VIEW_UNIFORM_MATRIX_H_

#include "gl_adapters/uniform_matrix.h"

struct Shaders;

struct ModelViewUniformMatrix {
   ModelViewUniformMatrix(Shaders& shaders, const glm::mat4& model_matrix);

   // Just returns the modelView matrix and the normal matrix. I swear.
   AffineUniforms calculateAffineUniforms(const glm::mat4& view_matrix) const;

   glm::mat4 model_matrix;

  private:
   GLUniformLocationMap model_view_uniforms_, normal_uniforms_;
};

#endif // MODEL_VIEW_UNIFORM_MATRIX_H_
