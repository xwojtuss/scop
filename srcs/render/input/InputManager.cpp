#include "InputManager.hpp"

using namespace render::input;

InputManager::InputManager() : m_currentCommand{}, m_mouseProcessor(0.01f) {
}

const InputCommand&	InputManager::getCurrentCommand() const {
	return m_currentCommand;
}

const InputCommand&	InputManager::getPreviousCommand() const {
	return m_previousCommand;
}

const InputCommand	InputManager::getDeltaCommand() const {
	InputCommand delta{};
	delta.moveForward = m_currentCommand.moveForward - m_previousCommand.moveForward;
	delta.moveRight = m_currentCommand.moveRight - m_previousCommand.moveRight;
	delta.lookUp = m_currentCommand.lookUp - m_previousCommand.lookUp;
	delta.lookRight = m_currentCommand.lookRight - m_previousCommand.lookRight;
	delta.eventBits = m_currentCommand.eventBits ^ m_previousCommand.eventBits;

	return delta;
}

void	InputManager::resetCommand() {
	m_mouseProcessor.reset();
	m_previousCommand = m_currentCommand;
	m_currentCommand = {};
}

void	InputManager::processMouseMove(double xpos, double ypos) {
	m_mouseProcessor.processMouseMove(-xpos, -ypos, m_currentCommand);
}

InputManager::~InputManager() {
}
