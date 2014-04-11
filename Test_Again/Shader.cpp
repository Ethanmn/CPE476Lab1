#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

const std::string kShaderPath = "../shaders/";

namespace {
   std::string shader_type_str(GLenum shader_type) {
      switch(shader_type)
      {
         case GL_VERTEX_SHADER:   return "vertex";
         case GL_GEOMETRY_SHADER: return "geometry";
         case GL_FRAGMENT_SHADER: return "fragment";
      }
      return "";
   }

   std::string read_file(const std::string& path) {
      std::ifstream source_stream(path);
      std::stringstream source_buffer;
      source_buffer << source_stream.rdbuf();
      return source_buffer.str();
   }

   GLuint createShader(GLenum shader_type, const std::string& path) {
      std::string file_source(read_file(path));
      std::string source_str(file_source.substr(0, file_source.length()-1));

      GLuint shader = glCreateShader(shader_type);
      const char *source = source_str.c_str();
      glShaderSource(shader, 1, &source, NULL);

      glCompileShader(shader);
      GLint status;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
      if (status == GL_FALSE) {
         GLint log_length;
         glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

         GLchar info_log[4096];
         glGetShaderInfoLog(shader, log_length, NULL, info_log);

         printf("Compile failure in %s shader:\n%s\n", shader_type_str(shader_type).c_str(), info_log);
         exit(EXIT_FAILURE);
      }

      return shader;
   }

   GLuint compileAndLinkShader(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
      GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_path);
      GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_path);

      GLuint program = glCreateProgram();
      glAttachShader(program, vertex_shader);
      glAttachShader(program, fragment_shader);

      glLinkProgram(program);
      GLint status;
      glGetProgramiv(program, GL_LINK_STATUS, &status);
      if (status == GL_FALSE) {
         GLint log_length;
         glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

         GLchar info_log[4096];
         glGetProgramInfoLog(program, log_length, NULL, info_log);
         printf("Shader linker failure: %s\n", info_log);
      }

      glDetachShader(program, vertex_shader);
      glDetachShader(program, fragment_shader);

      return program;
   }
}

Shader::Shader(const std::string& name, const std::vector<std::string>& attributes) :
   program_(compileAndLinkShader(kShaderPath + name + ".vert", kShaderPath + name + ".frag"))
{
   for (const auto& attr : attributes) {
      attribute_locations_.insert(std::make_pair(attr, glGetAttribLocation(program_, attr.c_str())));
   }
}

void Shader::bindAndEnableAttribute(
      GLuint buffer_object,
      const std::string& attribute,
      size_t num_components) {
   glBindBuffer(GL_ARRAY_BUFFER, buffer_object);

   const GLint attrib_location = attribute_locations_.at(attribute);
   glVertexAttribPointer(attrib_location, num_components, GL_FLOAT, GL_FALSE, 0, nullptr);
   glEnableVertexAttribArray(attrib_location);
}