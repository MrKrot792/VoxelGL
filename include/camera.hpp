#pragma once

#include "glm/ext.hpp"
#include "glm/mat4x4.hpp"
#include "glm/trigonometric.hpp"
#include "glm/vec3.hpp"

namespace Camera
{
inline glm::vec3 position{};
inline glm::vec3 rotation{};

constexpr glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

inline glm::mat4 getViewMatrix()
{
    float pitch = rotation.x;
    float yaw = rotation.y;

    glm::vec3 forward;
    forward.x = cos(pitch) * cos(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * sin(yaw);
    forward = glm::normalize(forward);

    glm::vec3 right = glm::normalize(glm::cross(forward, cameraUp));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    return glm::lookAt(position, position + forward, up);
}
}; // namespace Camera
