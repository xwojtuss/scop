#include "APanel.hpp"

using namespace render::gui;

APanel::APanel(IGui& gui) : m_gui(gui), m_isOpen(false) {
}

void	APanel::open() {
	m_isOpen = true;
}

void	APanel::toggle() {
	m_isOpen = !m_isOpen;
}

void	APanel::close() {
	m_isOpen = false;
}

bool	APanel::isOpen() const {
	return m_isOpen;
}
