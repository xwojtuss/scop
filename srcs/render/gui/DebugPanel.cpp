#include "DebugPanel.hpp"

#include <imgui.h>

using namespace render::gui;

DebugPanel::DebugPanel(IGui& gui) : APanel(gui) {
}

void	DebugPanel::display() {
	bool isWindowVisible = m_gui.beginWindow("Debug", &m_isOpen);
	if (isWindowVisible) {
		m_gui.text("This is a debug panel where coords and fps will be displayed");
		if (m_gui.button("Close"))
			m_isOpen = false;
	}
	m_gui.endWindow();
}
