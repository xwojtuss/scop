#include "InputManager.hpp"

using namespace render::input;

InputManager::InputManager() : m_mouseProcessor(0.005f) {
}

InputCommand	InputManager::buildCommand() {
	InputCommand command = {};

	double deltaX, deltaY;
	m_mouseProcessor.getMouseDelta(&deltaX, &deltaY);

	command.lookRight += static_cast<float>(deltaX);
	command.lookUp += static_cast<float>(deltaY);

	return command;
}

void	InputManager::processMouseMove(double xpos, double ypos) {
	m_mouseProcessor.processMouseMove(-xpos, -ypos);
}

void	InputManager::processMouseButton(int button, InputActions action) {
	m_mouseProcessor.processMouseButton(button, action);
}

InputManager::~InputManager() {
}
