#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <string>

enum class Attribute {
   VERTEX,
   NORMAL,
};

inline std::string attribute_name(Attribute attribute) {
   switch (attribute) {
      case Attribute::VERTEX:
         return "aPosition";
      case Attribute::NORMAL:
         return "aNormal";
   }
}

#endif // ATTRIBUTES_H_
