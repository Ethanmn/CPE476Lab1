#ifndef GL_TYPES_H_
#define GL_TYPES_H_

#include <GL/glew.h>
#include <boost/serialization/strong_typedef.hpp>

BOOST_STRONG_TYPEDEF(GLint, GLAttributeLocation)
BOOST_STRONG_TYPEDEF(GLint, GLUniformLocation)
BOOST_STRONG_TYPEDEF(GLuint, GLShaderHandle)
BOOST_STRONG_TYPEDEF(GLuint, GLBufferHandle)

#endif // GL_TYPES_H_
