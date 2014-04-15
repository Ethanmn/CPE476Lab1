#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera() :
   world_position_(glm::vec3(0, 0, -3))
      {}

void Camera::translateLocal(float amount, const glm::vec3& axis) {
   world_position_ += amount * fromLocalAxis(axis);
}

void Camera::rotateLocal(float degrees, const glm::vec3& axis) {
   world_rotation_ = glm::rotate(
         world_rotation_,
         degrees,
         fromLocalAxis(axis));
}

glm::vec3 Camera::fromLocalAxis(const glm::vec3& axis) const {
   return glm::normalize(glm::vec3(glm::vec4(axis, 0) * world_rotation_));
}

glm::mat4 Camera::viewMatrix() const {
   return glm::lookAt(
         world_position_,
         world_position_ + fromLocalAxis(kForwardVec),
         kUpVec);
}
