#include "DebugPanel.hpp"

#include <imgui.h>

using namespace render::gui;

DebugPanel::DebugPanel(IGui& gui, ecs::World& world) : APanel(gui), m_world(world) {
}

void	DebugPanel::display() {
	ecs::component::Transform* transform = m_world.getComponentManager<ecs::component::Transform>().getComponent(m_caller);

	if (!transform)
		return;

	glm::vec3 pos = transform->position;
	if (m_gui.beginWindow("Debug", &m_isOpen)) {
		m_gui.text("Player Position: X:" + std::to_string(pos.x) + ", Y:" + std::to_string(pos.y) + ", Z:" + std::to_string(pos.z));
	}
	m_gui.endWindow();
}
