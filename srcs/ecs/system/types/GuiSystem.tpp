#pragma once

#include "GuiSystem.hpp"

namespace ecs {
template<typename PanelType>
void	GuiSystem::registerPanel(render::input::InputEvent toggleEvent) {
	std::type_index typeIdx = std::type_index(typeid(PanelType));
	
	m_panels.emplace(typeIdx, std::make_unique<PanelType>(m_gui));
	
	m_eventToPanelType.emplace(toggleEvent, typeIdx);
}

template<typename PanelType>
PanelType*	GuiSystem::getPanel() {
	std::type_index typeIdx = std::type_index(typeid(PanelType));
	auto it = m_panels.find(typeIdx);
	
	if (it != m_panels.end()) {
		return static_cast<PanelType*>(it->second.get());
	}
	
	return nullptr;
}
}
