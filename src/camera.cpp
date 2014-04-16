#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

const auto kPitchLimit = 45.0f;

Camera::Camera() :
   world_position_(glm::vec3(0, 0, -3))
      {}

void Camera::translateForward(float amount) {
   world_position_ += amount * unitDirection();
   world_position_.y = std::max(0.0f, world_position_.y);
}

void Camera::translateStrafe(float amount) {
   world_position_ += amount * glm::normalize(glm::cross(unitDirection(), kUpVec));
}

void Camera::rotatePitch(float degrees) {
   pitch_ = std::max(-kPitchLimit, std::min(kPitchLimit, pitch_ + degrees));
}

glm::mat4 Camera::viewMatrix() const {
   return glm::lookAt(
         world_position_,
         world_position_ + unitDirection(),
         kUpVec);
}

glm::vec3 Camera::unitDirection() const {
   return glm::normalize(glm::rotateY(glm::rotateX(glm::vec3(0, 0, 1), pitch_), yaw_));
}
