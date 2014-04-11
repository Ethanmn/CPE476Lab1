#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>

enum class ShaderType {
   GROUND_SHADER,
   NUM_SHADER_TYPES,
};

struct Shader {
   Shader(ShaderType shader);
   void use() { glUseProgram(program_); }

  private:
   GLuint program_;
};

#endif // SHADER_H_
