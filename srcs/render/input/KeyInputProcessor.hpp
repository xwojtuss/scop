#pragma once

#include <stdexcept>

#include "InputTypes.hpp"
#include "../../platform/input/glfw/GLFWInput.hpp"
#include "../../platform/input/glfw/GLFWDefaultKeybinds.hpp"

namespace render::input {
class KeyInputProcessor {
public:
	constexpr static size_t	maxEventActions = 64;
	
private:
	InputEventBindings	m_bindings;
	InputEvents			m_pressedEvents;
	InputEvents			m_repeatedEvents;
	InputEvents			m_releasedEvents;
	InputEvents			m_activeEvents;

	void	switchEvent(InputEvent event, InputAction action);

public:
	KeyInputProcessor();
	~KeyInputProcessor();

	void	processKey(int scancode, InputAction action, InputMods modifiers);
	void	getKeyEvents(InputEvents& pressedEvents, InputEvents& repeatedEvents, InputEvents& releasedEvents, InputEvents& activeEvents);
	void	processMouseButton(MouseButton button, InputAction action, InputMods modifiers);
	void	bindEvent(Input input, InputEvent event);
	void	resetBindings();
};
}
