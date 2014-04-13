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

Shader::Shader(
      const std::string& name,
      const std::vector<std::string>& attributes,
      const std::vector<std::string>& uniforms) :
   gl_shader_(compileAndLinkShader(kShaderPath + name + ".vert", kShaderPath + name + ".frag"))
{
   for (const auto& attr : attributes) {
      attribute_locations_.insert(std::make_pair(
               attr,
               gl_shader_.getAttributeLocation(attr)));
   }
   for (const auto& uniform : uniforms) {
      uniform_locations_.insert(std::make_pair(
               uniform,
               gl_shader_.getUniformLocation(uniform)));
   }
}

void Shader::use() {
   gl_shader_.use();
}

void Shader::drawMesh(const IndexBufferObject& index_buffer, const std::vector<ArrayBufferObject>& array_buffer_objects) {
   bindIndexBuffer(index_buffer);
   bindAndEnableAttributes(array_buffer_objects);
   glDrawElements(GL_TRIANGLES, index_buffer.size, GL_UNSIGNED_SHORT, 0);
   disableAttributes(array_buffer_objects);
}

void Shader::bindIndexBuffer(const IndexBufferObject& index_buffer) {
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.handle);
}

void Shader::bindAndEnableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects) {
   for (const auto& buffer_object : array_buffer_objects) {
      gl_shader_.bindAndEnableAttribute(buffer_object);
   }
}

void Shader::disableAttributes(const std::vector<ArrayBufferObject>& array_buffer_objects) {
   for (const auto& buffer_object : array_buffer_objects) {
      gl_shader_.disableAttribute(buffer_object);
   }
}
