#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <map>
#include <string>
#include <GL/glew.h>

enum class ShaderType {
   GROUND,
};

struct Shaders {
   Shaders();

   void use(ShaderType shader) {
      if (programs_.count(shader) > 0) {
         glUseProgram(programs_[shader]);
      } else {
         std::cerr << "Uninitialized ShaderType. ";
         std::cerr << "Perhaps you meant to initialize it in Shaders::Shaders()?" << std::endl;
         exit(EXIT_FAILURE);
      }
   }

   void clear() {
      glUseProgram(0);
   }

  private:
   std::map<ShaderType, GLuint> programs_;
};

#endif // SHADER_H_
