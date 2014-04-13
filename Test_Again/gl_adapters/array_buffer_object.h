#ifndef ARRAY_BUFFER_OBJECT_H_
#define ARRAY_BUFFER_OBJECT_H_

#include <GL/glew.h>
#include "gl_shader.h"

#include <map>

struct ArrayBufferObject {
   GLShaderHandle handle; // Handle for where the Array Buffer is stored.
   // Location of the attribute in the given shader program.
   std::map<GLShaderHandle, GLint> attribute_locations;
   size_t num_components; // E.g. Array of vec3s is 3 components.
};

#endif // ARRAY_BUFFER_OBJECT_H_
