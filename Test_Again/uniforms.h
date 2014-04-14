#ifndef UNIFORMS_H_
#define UNIFORMS_H_

#include <string>

enum class Uniform {
   MODEL,
   VIEW,
   PROJECTION,
   NORMAL
};

inline std::string uniform_name(Uniform uniform) {
   switch (uniform) {
      case Uniform::MODEL:
         return "uModelMatrix";
      case Uniform::VIEW:
         return "uViewMatrix";
      case Uniform::PROJECTION:
         return "uProjectionMatrix";
      case Uniform::NORMAL:
         return "uNormalMatrix";
   }
}

#endif // UNIFORMS_H_
