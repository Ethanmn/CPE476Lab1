#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

struct Shader {
   Shader(const std::string& name, const std::vector<std::string>& attributes);

   void use() { glUseProgram(program_); }
   void bindAndEnableAttribute(
         GLuint buffer_object,
         const std::string& attribute,
         size_t num_components);
   void disableAttribute(const std::string& attribute) {
      glDisableVertexAttribArray(attribute_locations_[attribute]);
   }

  private:
   GLuint program_;
   std::map<std::string, GLint> attribute_locations_;
};

#endif // SHADER_H_
