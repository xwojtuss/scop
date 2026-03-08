#pragma once

#include <sstream>

#include "APanel.hpp"
#include "../../ecs/World.hpp"
#include "../../ecs/component/Components.hpp"

namespace render::gui {
class PlayerComponentsPanel : public APanel {
private:
	ecs::World&	m_world;

public:
	PlayerComponentsPanel(IGui& gui, ecs::World& world);

	void	display() override;
};
}