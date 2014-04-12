#ifndef ARRAY_BUFFER_OBJECT_H_
#define ARRAY_BUFFER_OBJECT_H_

#include <GL/glew.h>

struct ArrayBufferObject {
   GLuint handle; // Handle for where the Array Buffer is stored.
   GLint attribute_location; // Location of the attribute in the shader program.
   size_t num_components; // E.g. Array of vec3s is 3 components.
};

#endif // ARRAY_BUFFER_OBJECT_H_
