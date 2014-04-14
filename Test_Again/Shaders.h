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

   Shader& at(ShaderType shader_type);
   void clear() { glUseProgram(0); }

   std::map<ShaderType, Shader>& getMap() { return shaders_; }
   GLUniformLocationMap getUniforms(const std::string& uniform);
   GLAttributeLocationMap getAttributes(const std::string& attribute);

  private:
   std::map<ShaderType, Shader> shaders_;
};

#endif // SHADERS_H_
