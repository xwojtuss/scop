#include "GLFWDefaultKeybinds.hpp"

using namespace platform::input::glfw;

render::input::InputEventBindings GLFWDefaultKeybinds::getDefaultBindings() {
	render::input::InputEventBindings bindings;

	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_W), 0)] = render::input::InputEvent::MoveForward;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_S), 0)] = render::input::InputEvent::MoveBackward;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_D), 0)] = render::input::InputEvent::MoveRight;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_A), 0)] = render::input::InputEvent::MoveLeft;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_SPACE), 0)] = render::input::InputEvent::Jump;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_LEFT_CONTROL), 0)] = render::input::InputEvent::Crouch;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_LEFT_CONTROL), GLFW_MOD_CONTROL)] = render::input::InputEvent::Crouch;

	return bindings;
}