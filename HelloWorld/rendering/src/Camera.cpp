//
// Created by masterktos on 14.11.22.
//

#include "include/render/Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

glm::mat4 Camera::LookAt() const {
    return glm::lookAt(Position(),
                       glm::vec3(0.0, 0.0, 0.0),
                       glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Camera::Projection(float aspect) const {
    return glm::perspective(glm::radians(fov), aspect,clipNear,clipFar);
}

glm::vec3 Camera::Position() const {
    return glm::vec3(sin(glm::radians(orbitAngle)) * orbitDistance,
                     sin(glm::radians(panAngle)) * orbitDistance,
                     cos(glm::radians(orbitAngle)) * orbitDistance);
}
