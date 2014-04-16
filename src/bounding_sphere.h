#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <glm/glm.hpp>

#include "bounds.h"

struct BoundingSphere {
   enum class Axis {
      X, Y, Z
   };

   bool collides(const BoundingSphere& o) const {
      return glm::distance(center, o.center) < radius + o.radius;
   }

   glm::vec3 center;
   float radius;
};

#endif // BOUNDING_SPHERE_H_
