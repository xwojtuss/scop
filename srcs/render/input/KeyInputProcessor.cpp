#include "KeyInputProcessor.hpp"

using namespace render::input;

KeyInputProcessor::KeyInputProcessor() : m_bindings(), m_pressedEvents(0), m_repeatedEvents(0), m_releasedEvents(0), m_activeEvents(0) {
}

void	KeyInputProcessor::processKey(int scancode, InputAction action, InputMods modifiers) {
	Input input = createInput(scancode, modifiers);

	auto it = m_bindings.find(input);
	if (it == m_bindings.end()) 
		return;
	
	InputEvent event = it->second;
	switch (action) {
		case InputAction::Press:
			m_pressedEvents |= event;
			m_activeEvents |= event;
			break;
		case InputAction::Release:
			m_releasedEvents |= event;
			m_activeEvents &= ~event;
			break;
		case InputAction::Repeat:
			m_repeatedEvents |= event;
			break;
		default:
			break;
	}
}

void	KeyInputProcessor::getKeyEvents(InputEvents& pressedEvents, InputEvents& repeatedEvents, InputEvents& releasedEvents, InputEvents& activeEvents) {
	pressedEvents = m_pressedEvents;
	repeatedEvents = m_repeatedEvents;
	releasedEvents = m_releasedEvents;
	activeEvents = m_activeEvents;
	m_pressedEvents = 0;
	m_repeatedEvents = 0;
	m_releasedEvents = 0;
}

void	KeyInputProcessor::bindEvent(Input input, InputEvent event) {
	m_bindings[input] = event;
}

void	KeyInputProcessor::resetBindings() {
	m_bindings = platform::input::glfw::GLFWDefaultKeybinds::getDefaultBindings();

	if (m_bindings.empty()) {
		throw std::runtime_error("Attempted to initialize bindings before glfw was initialized");
	}
}

KeyInputProcessor::~KeyInputProcessor() {
}
