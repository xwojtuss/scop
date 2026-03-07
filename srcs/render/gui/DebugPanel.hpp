#pragma once

#include "APanel.hpp"

namespace render::gui {
class DebugPanel : public APanel {
private:
public:
	DebugPanel(IGui& gui);

	void	display() override;
};
}