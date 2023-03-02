//
// Created by masterktos on 14.11.22.
//

#ifndef OPENGLGP_CAMERA_H
#define OPENGLGP_CAMERA_H

#include "glm/detail/type_mat4x4.hpp"

class Camera {
    // variables
public:
    float orbitAngle = 0;
    float orbitDistance = 50;
    float panAngle = 3;
    float fov = 45.0f;
    float clipNear = 0.1f;
    float clipFar = 1000.0f;
    //methods
public:
    glm::vec3 Position() const;
    glm::mat4 LookAt() const;
    glm::mat4 Projection(float aspect) const;
};


#endif //OPENGLGP_CAMERA_H
