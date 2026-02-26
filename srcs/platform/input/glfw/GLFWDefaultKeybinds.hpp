#pragma once

#include <GLFW/glfw3.h>

#include "../../../render/input/InputTypes.hpp"

namespace platform::input::glfw {
class GLFWDefaultKeybinds {
public:
	GLFWDefaultKeybinds();

	static render::input::InputEventBindings	getDefaultBindings();
};
}
