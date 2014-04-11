#include "Shaders.h"

#include <assert.h>

const std::vector<std::string> kGroundAttrs({ "aPosition" });

Shaders::Shaders() {
   shaders_.insert(std::make_pair(ShaderType::GROUND, Shader("ground", kGroundAttrs)));
}
