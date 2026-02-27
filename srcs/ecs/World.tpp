#pragma once

#include "World.hpp"

using namespace ecs;

template <typename ComponentType>
ComponentManager<ComponentType>&	World::getComponentManager() {
	int componentId = ComponentType::getId();

	if (componentId >= static_cast<int>(m_componentManagers.size())) {
		m_componentManagers.resize(componentId + 1);

		m_componentManagers[componentId] = std::make_unique<ComponentManager<ComponentType>>();
	}
	return *static_cast<ComponentManager<ComponentType>*>(m_componentManagers[componentId].get());
}

template <typename SystemType>
void	World::createSystem() {
	SystemType& system = m_systemManager.addSystem<SystemType>();
	system.registerWorld(this);
	system.subscribe(m_systemManager.getDispatcher());
}
