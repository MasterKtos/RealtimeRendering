//
// Created by MasterKtos on 25.11.2022.
//

#ifndef OPENGLGP_FPPCAMERA_H
#define OPENGLGP_FPPCAMERA_H

#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class FPPCamera {
private:
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;
    float pitch = 0;

    bool firstMouse = true;
    void updateCameraVectors();
public:
    // Variables
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right;

    float fov = 45.0f;
    float clipNear = 0.1f;
    float clipFar = 1000.0f;

    float speed = 25.0f;
    float sensivity = 0.1f;


    //Methods
    FPPCamera();

    void ProcessKeyboardInput(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    glm::mat4 LookAt() const;
    glm::mat4 Projection(float aspect) const;
};


#endif //OPENGLGP_FPPCAMERA_H
