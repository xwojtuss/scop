#pragma once

#include "InputTypes.hpp"

namespace render::input {
class MouseInputProcessor {
private:
	float	m_sensitivity;
	double	m_lastMouseX;
	double	m_lastMouseY;
	double	m_accumulatedMouseX;
	double	m_accumulatedMouseY;

public:
	MouseInputProcessor(float sensitivity);
	~MouseInputProcessor();

	void	processMouseMove(double xpos, double ypos);
	void	processMouseButton(int button, InputActions action);
	void	getMouseDelta(double* deltaX, double* deltaY);
};
}