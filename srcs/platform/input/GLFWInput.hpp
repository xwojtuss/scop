#pragma once

#include <GLFW/glfw3.h>

#include "../../render/input/InputTypes.hpp"

namespace platform::input::glfw {
render::input::InputActions	glfwToInputAction(int glfwAction);
}
