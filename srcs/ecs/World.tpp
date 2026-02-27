#pragma once

#include "World.hpp"

using namespace ecs;

template <typename ComponentType>
ComponentManager<ComponentType>&	World::getComponentManager() {
	int componentId = ComponentType::getId();
	
	if (m_componentManagers.find(componentId) == m_componentManagers.end()) {
		m_componentManagers[componentId] = std::make_unique<ComponentManager<ComponentType>>();
	}

	return *static_cast<ComponentManager<ComponentType>*>(m_componentManagers[componentId].get());
}

template <typename SystemType, typename... Args>
void	World::createSystem(Args&&... args) {
	SystemType& system = m_systemManager.addSystem<SystemType>(args...);
	system.registerWorld(this);
	system.bindEvents(m_systemManager.getDispatcher());
}

template <typename SystemType, typename... Args>
void	World::createDispatchingSystem(Args&&... args) {
	SystemType& system = m_systemManager.addSystem<SystemType>(args..., m_systemManager.getDispatcher());
	system.registerWorld(this);
	system.bindEvents(m_systemManager.getDispatcher());
}
