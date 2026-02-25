#include "MouseInputProcessor.hpp"

using namespace render::input;

MouseInputProcessor::MouseInputProcessor(const float sensitivity) : m_sensitivity(sensitivity) {
}

void	MouseInputProcessor::processMouseMove(double xpos, double ypos, InputCommand& command) {
	if (m_firstMouse) {
		m_lastMouseX = xpos;
		m_lastMouseY = ypos;
		m_firstMouse = false;
		return;
	}

	const double deltaX = xpos - m_lastMouseX;
	const double deltaY = ypos - m_lastMouseY;

	m_lastMouseX = xpos;
	m_lastMouseY = ypos;

	command.lookRight += static_cast<float>(deltaX) * m_sensitivity;
	command.lookUp += static_cast<float>(deltaY) * m_sensitivity;
}

void	MouseInputProcessor::reset() {
	m_firstMouse = true;
	m_lastMouseX = 0.0;
	m_lastMouseY = 0.0;
}

MouseInputProcessor::~MouseInputProcessor() {
}
