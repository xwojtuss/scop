#pragma once

#include "MouseInputProcessor.hpp"
#include "KeyInputProcessor.hpp"
#include "InputTypes.hpp"

namespace render::input {
class InputManager {
private:
	MouseInputProcessor	m_mouseProcessor;
	KeyInputProcessor	m_keyInputProcessor;

public:
	InputManager();
	~InputManager();

	InputCommand		buildCommand();
	void				processMouseMove(double xpos, double ypos);
	void				processMouseButton(int button, InputAction action, InputMods modifiers);
	void				processKey(int scancode, InputAction action, InputMods modifiers);
	KeyInputProcessor&	getKeyInputProcessor();
};
}
