#ifndef PROJECTION_H_
#define PROJECTION_H_

#include <glm/glm.hpp>

#include "gl_adapters/gl_types.h"

struct Shader;
struct Shaders;

struct Projection {
   Projection(Shaders& shaders);

   void sendToShader(Shader& shader);
  private:
   glm::mat4 projection_matrix_;
   GLUniformLocationMap projection_uniforms_;
};

#endif // PROJECTION_H_
