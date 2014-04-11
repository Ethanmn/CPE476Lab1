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

struct IndexBufferObject {
   GLuint handle;
   size_t size;
};

template <typename T>
GLuint createBufferObject(const std::vector<T>& data) {
   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
   return vbo;
}

IndexBufferObject createIndexBufferObject(const std::vector<unsigned short>& data);

template <typename T>
ArrayBufferObject createArrayBufferObject(const std::vector<T>& data, const std::string& attribute, size_t num_components) {
   return ArrayBufferObject{createBufferObject(data), attribute, num_components};
}

#endif // BUFFER_OBJECT_H_
