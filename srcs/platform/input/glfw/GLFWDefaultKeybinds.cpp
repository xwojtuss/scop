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
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_ESCAPE), 0)] = render::input::InputEvent::ToggleCursor;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_F), 0)] = render::input::InputEvent::ToggleShader;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_8), 0)] = render::input::InputEvent::ArrowMoveForward;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_2), 0)] = render::input::InputEvent::ArrowMoveBackward;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_6), 0)] = render::input::InputEvent::ArrowMoveRight;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_4), 0)] = render::input::InputEvent::ArrowMoveLeft;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_9), 0)] = render::input::InputEvent::ArrowMoveUp;
	bindings[render::input::createInput(glfwGetKeyScancode(GLFW_KEY_KP_3), 0)] = render::input::InputEvent::ArrowMoveDown;

	bindings[render::input::createMouseInput(render::input::MouseButton::LeftButton, 0)] = render::input::InputEvent::SecondaryButton;
	bindings[render::input::createMouseInput(render::input::MouseButton::RightButton, 0)] = render::input::InputEvent::ActionButton;

	return bindings;
}