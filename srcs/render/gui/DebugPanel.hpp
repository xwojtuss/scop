#pragma once

#include "APanel.hpp"
#include "../../ecs/World.hpp"
#include "../../ecs/component/Components.hpp"

namespace render::gui {
class DebugPanel : public APanel {
private:
	ecs::World&	m_world;

public:
	DebugPanel(IGui& gui, ecs::World& world);

	void	display() override;
};
}