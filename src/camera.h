#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "vec_constants.h"

struct Camera {
   Camera();

   // Convert axis from local space before translate/rotate.
   void translateLocal(float amount, const glm::vec3& local_axis);
   void rotateLocal(float angle, const glm::vec3& local_axis);

   glm::mat4 viewMatrix() const;

  private:
   glm::vec3 fromLocalAxis(const glm::vec3& axis) const;

   glm::vec3 world_position_;
   glm::quat world_rotation_;
};

#endif // CAMERA_H_
