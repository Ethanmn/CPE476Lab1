#ifndef BUFFER_OBJECT_H_
#define BUFFER_OBJECT_H_

#include <GL/glew.h>
#include <string>
#include <vector>

struct ArrayBufferObject {
   GLuint handle;
   const std::string attribute;
   size_t num_components;
};

template <typename T>
ArrayBufferObject createArrayBufferObject(const std::vector<T>& data, const std::string& attribute, size_t num_components) {
   {
      GLuint vao;
      glGenBuffers(1, &vao);
      glBindVertexArray(vao);
   }

   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   return ArrayBufferObject{vbo, attribute, num_components};
}

#endif // BUFFER_OBJECT_H_
