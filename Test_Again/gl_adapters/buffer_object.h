#ifndef BUFFER_OBJECT_H_
#define BUFFER_OBJECT_H_

#include <GL/glew.h>
#include <vector>

#include "gl_adapters/array_buffer_object.h"
#include "gl_adapters/index_buffer_object.h"

template <typename T>
GLuint createBufferObject(const std::vector<T>& data) {
   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
   return vbo;
}

#endif // BUFFER_OBJECT_H_
