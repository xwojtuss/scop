#include "InputManager.hpp"

using namespace render::input;

InputManager::InputManager() : m_mouseProcessor(0.1f), m_keyInputProcessor() {
}

InputCommand	InputManager::buildCommand() {
	InputCommand command = {};

	double deltaX, deltaY;
	m_mouseProcessor.getMouseDelta(deltaX, deltaY);

	command.lookRight += static_cast<float>(deltaX);
	command.lookUp += static_cast<float>(deltaY);

	InputEvents pressedEvents, repeatedEvents, releasedEvents, activeEvents;
	m_keyInputProcessor.getKeyEvents(pressedEvents, repeatedEvents, releasedEvents, activeEvents);

	command.startedEvents = pressedEvents;
	command.repeatedEvents = repeatedEvents;
	command.stoppedEvents = releasedEvents;
	command.activeEvents = activeEvents;

	command.moveForward = hasEvent(activeEvents, InputEvent::MoveForward) * 1.0f;
	command.moveForward -= hasEvent(activeEvents, InputEvent::MoveBackward) * 1.0f;
	command.moveRight = hasEvent(activeEvents, InputEvent::MoveRight) * 1.0f;
	command.moveRight -= hasEvent(activeEvents, InputEvent::MoveLeft) * 1.0f;
	command.moveUp = hasEvent(activeEvents, InputEvent::Jump) * 1.0f;
	command.moveUp -= hasEvent(activeEvents, InputEvent::Crouch) * 1.0f;
	
	return command;
}

void	InputManager::processMouseMove(double xpos, double ypos) {
	m_mouseProcessor.processMouseMove(-xpos, -ypos);
}

void	InputManager::processMouseButton(int button, InputAction action) {
	m_mouseProcessor.processMouseButton(button, action);
}

void	InputManager::processKey(int scancode, InputAction action, InputMods modifiers) {
	m_keyInputProcessor.processKey(scancode, action, modifiers);
}

KeyInputProcessor&	InputManager::getKeyInputProcessor() {
	return m_keyInputProcessor;
}

InputManager::~InputManager() {
}
