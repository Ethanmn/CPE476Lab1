#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <string>

enum class Attribute {
   VERTEX,
};

inline std::string attribute_name(Attribute attribute) {
   switch (attribute) {
      case Attribute::VERTEX:
         return "aPosition";
   }
}

#endif // ATTRIBUTES_H_
