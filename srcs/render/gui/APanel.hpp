#pragma once

#include "IGui.hpp"

namespace render::gui {
constexpr const size_t	maxPanels = 32;

class APanel {
protected:
	IGui&	m_gui;
	bool	m_isOpen = false;

	APanel(IGui& gui);

public:
	virtual ~APanel() = default;

	virtual void	open();
	virtual void	display() = 0;
	virtual void	close();
	void			toggle();
	bool			isOpen() const;
};
}
