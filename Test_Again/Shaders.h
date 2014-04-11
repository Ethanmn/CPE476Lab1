#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Shader.h"

enum class ShaderType {
   GROUND,
};

struct Shaders {
   Shaders();

   Shader& use(ShaderType shader_type) {
      if (shaders_.count(shader_type) > 0) {
         Shader& shader = shaders_.at(shader_type);
         shader.use();
         return shader;
      } else {
         std::cerr << "Uninitialized ShaderType. ";
         std::cerr << "Perhaps you meant to initialize it in Shaders::Shaders()?" << std::endl;
         exit(EXIT_FAILURE);
      }
   }

   void clear() { glUseProgram(0); }

  private:
   std::map<ShaderType, Shader> shaders_;
};

#endif // SHADERS_H_
