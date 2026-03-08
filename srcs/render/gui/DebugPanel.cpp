#include "DebugPanel.hpp"

#include <imgui.h>

using namespace render::gui;

DebugPanel::DebugPanel(IGui& gui, ecs::World& world) : APanel(gui), m_world(world) {
}

void	DebugPanel::display() {
	if (!m_isOpen)
		return;

	ecs::component::Transform* transform = m_world.getComponentManager<ecs::component::Transform>().getComponent(m_caller);

	if (!transform)
		return;

	std::stringstream ss;
	std::vector<ecs::IComponent*> components = m_world.getAllComponents(m_caller);
	if (m_gui.beginWindow("Debug", &m_isOpen)) {
		for (const auto& component : components) {
			if (m_gui.beginSection(component->getName().c_str())) {
				ss << *component;
				m_gui.text(ss.str());
				ss.str("");
			}
			m_gui.endSection();
		}
	}
	m_gui.endWindow();
}
