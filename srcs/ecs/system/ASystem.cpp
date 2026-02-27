#include "ASystem.hpp"
#include "../World.hpp"

using namespace ecs;

ASystem::ASystem(const Dependencies& dependencies) : m_dependencies(dependencies), m_world(nullptr) {
}

Dependencies	ASystem::getDependencies() const {
	return m_dependencies;
}

void	ASystem::registerEntity(const Entity& entity) {
	if (!canRegister(entity))
		return;

	m_entities.push_back(entity);
}

void	ASystem::unregisterEntity(const Entity& entity) {
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		if (*it == entity) {
			m_entities.erase(it);
			break;
		}
	}
}

void	ASystem::registerWorld(World* world) {
	m_world = world;
}

bool	ASystem::canRegister(const Entity& entity) const {
	if (!m_world)
		return false;

	IComponentManager* manager = nullptr;

	for (int i = 0; i < static_cast<int>(m_dependencies.mask.size()); ++i) {
		if (!m_dependencies.mask.test(i))
			continue;

		manager = m_world->getComponentManager(i);

		if (!manager || !manager->hasComponent(entity))
			return false;
	}
	return true;
}
