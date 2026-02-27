#include "World.hpp"

#include "entity/EntityHandle.hpp"

using namespace ecs;

EntityHandle	World::createEntity() {
	Entity entity = m_entityManager.createEntity();
	return EntityHandle{entity, this};
}

void	World::destroyEntity(const Entity& entity) {
	for (int i = 0; i < static_cast<int>(m_componentManagers.size()); ++i) {
		if (m_componentManagers[i] && m_componentManagers[i]->hasComponent(entity)) {
			m_componentManagers[i]->removeComponent(entity);
		}
	}
}

IComponentManager*	World::getComponentManager(int componentId) {
	if (componentId >= static_cast<int>(m_componentManagers.size())) {
		return nullptr;
	}
	return m_componentManagers[componentId].get();
}

SystemManager&	World::getSystemManager() {
	return m_systemManager;
}
