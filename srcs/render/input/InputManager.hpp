#pragma once

#include "MouseInputProcessor.hpp"
#include "InputTypes.hpp"

namespace render::input {
class InputManager {
private:
	MouseInputProcessor	m_mouseProcessor;

public:
	InputManager();
	~InputManager();

	InputCommand	buildCommand();
	void			processMouseMove(double xpos, double ypos);
	void			processMouseButton(int button, InputActions action);
};
}
