#pragma once

#include <glad/glad.h>
#include <glm/common.hpp>

class Camera {
public:
    Camera()
    {

    }

    virtual ~Camera();

    // private:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};