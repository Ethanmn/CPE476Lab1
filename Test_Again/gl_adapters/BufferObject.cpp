#include "BufferObject.h"

IndexBufferObject createIndexBufferObject(const std::vector<unsigned short>& data) {
   return IndexBufferObject{createBufferObject(data), data.size()};
}
