#include "Shaders.h"

#include <assert.h>

const std::vector<Attribute> kGroundAttrs{
   Attribute::VERTEX,
   Attribute::NORMAL
};
const std::vector<Uniform> kGroundUniforms{
   Uniform::MODEL,
   Uniform::VIEW,
   Uniform::PROJECTION,
   Uniform::NORMAL,
};

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

GLUniformLocationMap Shaders::getUniforms(const Uniform& uniform) {
   GLUniformLocationMap uniforms;
   for (auto& pair : shaders_) {
      uniforms.insert(pair.second.uniformLocation(uniform));
   }
   return uniforms;
}

GLAttributeLocationMap Shaders::getAttributes(const Attribute& attribute) {
   GLAttributeLocationMap attributes;
   for (auto& pair : shaders_) {
      attributes.insert(pair.second.attributeLocation(attribute));
   }
   return attributes;
}
