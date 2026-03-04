#pragma once

#include "InputTypes.hpp"

namespace render::input {
class MouseInputProcessor {
private:
	bool		m_hasLastMousePosition;
	double		m_lastMouseX;
	double		m_lastMouseY;
	double		m_accumulatedMouseX;
	double		m_accumulatedMouseY;

public:
	MouseInputProcessor();
	~MouseInputProcessor();

	void	processMouseMove(double xpos, double ypos);
	void	getMouseDelta(double& deltaX, double& deltaY);
	void	getMouseButtons(InputEvents& pressed, InputEvents& repeated, InputEvents& released, InputEvents& active);
};
}