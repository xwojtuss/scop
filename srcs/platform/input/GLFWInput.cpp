#include "GLFWInput.hpp"

namespace platform::input::glfw {

render::input::InputActions	glfwToInputAction(int glfwAction) {
	switch (glfwAction) {
		case GLFW_PRESS:
			return render::input::InputActions::Press;
		case GLFW_RELEASE:
			return render::input::InputActions::Release;
		case GLFW_REPEAT:
			return render::input::InputActions::Repeat;
		default:
			return render::input::InputActions::Release;
	}
}

}
