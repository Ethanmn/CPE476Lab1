#include "Shaders.h"

#include <assert.h>

const std::vector<std::string> kGroundAttrs{ "aPosition" };
const std::vector<std::string> kGroundUniforms{ "uProjectionMatrix" };

Shaders::Shaders() {
   shaders_.insert(std::make_pair(
            ShaderType::GROUND,
            Shader("ground", kGroundAttrs, kGroundUniforms)));
}

Shader& Shaders::at(ShaderType shader_type) {
   if (shaders_.count(shader_type) > 0) {
      return shaders_.at(shader_type);
   } else {
      std::cerr << "Uninitialized ShaderType. ";
      std::cerr << "Perhaps you meant to initialize it in Shaders::Shaders()?" << std::endl;
      exit(EXIT_FAILURE);
   }
}

GLUniformLocationMap Shaders::getUniforms(const std::string& uniform) {
   GLUniformLocationMap uniforms;
   for (auto& pair : shaders_) {
      uniforms.insert(pair.second.uniformLocation(uniform));
   }
   return uniforms;
}
