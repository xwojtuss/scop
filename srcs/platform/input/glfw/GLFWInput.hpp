#pragma once

#include <GLFW/glfw3.h>

#include "../../../render/input/InputTypes.hpp"

namespace platform::input::glfw {
render::input::InputAction		glfwToInputAction(int glfwAction);
render::input::InputMods		glfwToInputMods(int glfwMods);

render::input::MouseButton		glfwToMouseButton(int glfwButton);
}
