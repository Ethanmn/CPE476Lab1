#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <glm/glm.hpp>

struct BoundingSphere {
   glm::vec3 center;
   float radius;
};

#endif // BOUNDING_SPHERE_H_
