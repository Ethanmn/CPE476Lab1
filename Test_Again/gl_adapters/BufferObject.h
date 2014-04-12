#ifndef BUFFER_OBJECT_H_
#define BUFFER_OBJECT_H_

#include <GL/glew.h>
#include <string>
#include <vector>

struct ArrayBufferObject {
   GLuint handle; // Handle for where the Array Buffer is stored.
   GLint attribute_location; // Location of the attribute in the shader program.
   size_t num_components; // E.g. Array of vec3s is 3 components.
};

struct IndexBufferObject {
   GLuint handle; // Handle for where the Array Buffer is stored.
   size_t size; // Number of elements in the index_buffer.
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
ArrayBufferObject createArrayBufferObject(const std::vector<T>& data, GLint attribute, size_t num_components) {
   return ArrayBufferObject{createBufferObject(data), attribute, num_components};
}

#endif // BUFFER_OBJECT_H_
