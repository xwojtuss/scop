#include "DebugPanel.hpp"

#include <imgui.h>

using namespace render::gui;

DebugPanel::DebugPanel(IGui& gui) : APanel(gui) {
}

void	DebugPanel::open() {
	m_isOpen = true;
}

void	DebugPanel::display() {
	bool isWindowVisible = m_gui.beginWindow("Debug", glm::vec2(200.0f, 100.0f), &m_isOpen);
	if (isWindowVisible) {
		m_gui.text("GUI is owned by GuiSystem");
		if (m_gui.button("Close"))
			m_isOpen = false;
	}
	m_gui.endWindow();
}

void	DebugPanel::close() {
	m_isOpen = false;
}
