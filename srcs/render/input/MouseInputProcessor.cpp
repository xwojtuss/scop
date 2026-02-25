#include "MouseInputProcessor.hpp"

using namespace render::input;

MouseInputProcessor::MouseInputProcessor(const float sensitivity) : m_sensitivity(sensitivity), m_lastMouseX(0.0), m_lastMouseY(0.0), m_accumulatedMouseX(0.0), m_accumulatedMouseY(0.0) {
}

void	MouseInputProcessor::processMouseMove(double xpos, double ypos) {
	const double deltaX = xpos - m_lastMouseX;
	const double deltaY = ypos - m_lastMouseY;

	m_accumulatedMouseX += deltaX;
	m_accumulatedMouseY += deltaY;
	m_lastMouseX = xpos;
	m_lastMouseY = ypos;
}

void	MouseInputProcessor::getMouseDelta(double* deltaX, double* deltaY) {
	*deltaX = m_accumulatedMouseX * m_sensitivity;
	*deltaY = m_accumulatedMouseY * m_sensitivity;
	m_accumulatedMouseX = 0.0;
	m_accumulatedMouseY = 0.0;
}

void	MouseInputProcessor::processMouseButton(int button, InputActions action) {
	(void)button;
	(void)action;
}

MouseInputProcessor::~MouseInputProcessor() {
}
