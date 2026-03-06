#pragma once

#include "ftm/vec.hpp"

namespace scene::worldinfo {
constexpr ftm::vec3		right = ftm::vec3(1.0f, 0.0f, 0.0f);
constexpr ftm::vec3		left = -right;
constexpr ftm::vec3		up = ftm::vec3(0.0f, 1.0f, 0.0f);
constexpr ftm::vec3		down = -up;
constexpr ftm::vec3		forward = ftm::vec3(0.0f, 0.0f, -1.0f);
constexpr ftm::vec3		backward = -forward;

constexpr float			drag = 0.9999999f;
}
