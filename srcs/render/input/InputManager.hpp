#pragma once

#include "MouseInputProcessor.hpp"
#include "InputTypes.hpp"

namespace render::input {
class InputManager {
private:
	InputCommand		m_currentCommand;
	InputCommand		m_previousCommand;
	MouseInputProcessor	m_mouseProcessor;

public:
	InputManager();
	~InputManager();

	const InputCommand&	getCurrentCommand() const;
	const InputCommand&	getPreviousCommand() const;
	const InputCommand	getDeltaCommand() const;
	void				resetCommand();
	void				processMouseMove(double xpos, double ypos);
};
}
