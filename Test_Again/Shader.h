#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>

struct Shader {
   Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

  private:
   GLuint program_;
};

#endif // SHADER_H_
