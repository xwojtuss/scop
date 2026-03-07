#include "APanel.hpp"

using namespace render::gui;

APanel::APanel(IGui& gui) : m_gui(gui), m_isOpen(false) {
}

void	APanel::toggle() {
	m_isOpen = !m_isOpen;
}

bool	APanel::isOpen() const {
	return m_isOpen;
}
