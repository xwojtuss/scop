#pragma once

#include "InputTypes.hpp"

namespace render::input {
class MouseInputProcessor {
private:
	float	m_sensitivity;
	bool	m_firstMouse = true;
	double	m_lastMouseX = 0.0;
	double	m_lastMouseY = 0.0;

public:
	MouseInputProcessor(float sensitivity);
	~MouseInputProcessor();

	void	processMouseMove(double xpos, double ypos, InputCommand& command);
	void	reset();
};
}