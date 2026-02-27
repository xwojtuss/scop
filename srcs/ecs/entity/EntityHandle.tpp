#pragma once

#include "EntityHandle.hpp"

using namespace ecs;

template <typename ComponentType>
ComponentType*	EntityHandle::getComponent() {
	return world->getComponentManager<ComponentType>().getComponent(entity);
}

template <typename ComponentType>
bool	EntityHandle::hasComponent() const {
	return world->getComponentManager<ComponentType>().hasComponent(entity);
}

template <typename ComponentType>
void	EntityHandle::addComponent(const ComponentType& component) {
	world->getComponentManager<ComponentType>().addComponent(entity, component);
}

template <typename ComponentType>
void	EntityHandle::removeComponent() {
	world->getComponentManager<ComponentType>().removeComponent(entity);
}

template <typename SystemType>
void	EntityHandle::registerToSystem() {
	SystemType* system = world->getSystemManager().getSystem<SystemType>();
	if (system) {
		system->registerEntity(entity);
	}
}

template <typename SystemType>
void	EntityHandle::unregisterFromSystem() {
	SystemType* system = world->getSystemManager().getSystem<SystemType>();
	if (system) {
		system->unregisterEntity(entity);
	}
}
