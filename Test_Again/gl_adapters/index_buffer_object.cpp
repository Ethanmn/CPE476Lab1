#include "gl_adapters/index_buffer_object.h"

#include "gl_adapters/buffer_object.h"

IndexBufferObject createIndexBufferObject(const std::vector<unsigned short>& data) {
   return IndexBufferObject{createBufferObject(data), data.size()};
}
