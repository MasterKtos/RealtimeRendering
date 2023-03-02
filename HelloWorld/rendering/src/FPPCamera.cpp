//
// Created by MasterKtos on 25.11.2022.
//

#include "include/render/FPPCamera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

FPPCamera::FPPCamera() {}

glm::mat4 FPPCamera::LookAt() const {
    return glm::lookAt(pos, pos + front, up);
}

glm::mat4 FPPCamera::Projection(float aspect) const {
    return glm::perspective(glm::radians(fov), aspect,clipNear,clipFar);
}

void FPPCamera::ProcessKeyboardInput(Camera_Movement direction, float deltaTime) {
    float velocity = speed * deltaTime;
    if (direction == FORWARD)
        pos += front * velocity;
    if (direction == BACKWARD)
        pos -= front * velocity;
    if (direction == LEFT)
        pos -= right * velocity;
    if (direction == RIGHT)
        pos += right * velocity;
}

void FPPCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= sensivity;
    yoffset *= sensivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void FPPCamera::updateCameraVectors() {
    // calculate the new Front vector
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    // also re-calculate the Right and Up vector

    // normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}