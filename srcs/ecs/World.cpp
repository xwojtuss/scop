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
	auto it = m_componentManagers.find(componentId);
	if (it == m_componentManagers.end()) {
		return nullptr;
	}
	return it->second.get();
}

std::vector<IComponent*>	World::getAllComponents(const Entity& entity) {
	std::vector<IComponent*> components;
	IComponent* component = nullptr;

	for (const auto& [id, manager] : m_componentManagers) {
		if (manager->hasComponent(entity)) {
			manager->getComponent(entity, component);
			components.push_back(component);
		}
	}

	return components;
}

SystemManager&	World::getSystemManager() {
	return m_systemManager;
}
