#pragma once

#include <glm/vec3.hpp>

namespace scene::worldinfo {
constexpr glm::vec3		right = glm::vec3(1.0f, 0.0f, 0.0f);
constexpr glm::vec3		left = -right;
constexpr glm::vec3		up = glm::vec3(0.0f, 1.0f, 0.0f);
constexpr glm::vec3		down = -up;
constexpr glm::vec3		forward = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr glm::vec3		backward = -forward;

constexpr float			drag = 0.99f;
}
