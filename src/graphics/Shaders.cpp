#include "graphics/Shaders.h"

#include <assert.h>

const std::vector<Attribute> kTextAttrs{
   Attribute::VERTEX,
   Attribute::TEX_COORD,
};
const std::vector<Uniform> kTextUniforms{
   Uniform::TEXTURE,
   Uniform::COLOR,
};

const std::vector<Attribute> kGroundAttrs{
   Attribute::VERTEX,
   Attribute::NORMAL
};
const std::vector<Uniform> kGroundUniforms{
   Uniform::MODEL_VIEW,
   Uniform::PROJECTION,
   Uniform::NORMAL,
   Uniform::BLUE,
};

Shaders::Shaders() {
   shaders_.insert(std::make_pair(
            ShaderType::GROUND,
            Shader("ground", kGroundAttrs, kGroundUniforms)));
   shaders_.insert(std::make_pair(
            ShaderType::TEXT,
            Shader("text", kTextAttrs, kTextUniforms)));
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
      const auto maybe_location = pair.second.uniformLocation(uniform);
      if (maybe_location)
         uniforms.insert(*maybe_location);
   }
   return uniforms;
}

GLAttributeLocationMap Shaders::getAttributes(const Attribute& attribute) {
   GLAttributeLocationMap attributes;
   for (auto& pair : shaders_) {
      const auto maybe_location = pair.second.attributeLocation(attribute);
      if (maybe_location)
         attributes.insert(*maybe_location);
   }
   return attributes;
}
