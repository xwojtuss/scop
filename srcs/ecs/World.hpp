#pragma once

#include <memory>
#include <unordered_map>

#include "component/IComponentManager.hpp"
#include "component/ComponentManager.hpp"
#include "entity/EntityManager.hpp"
#include "system/SystemManager.hpp"

namespace ecs {
struct EntityHandle;

class World {
private:
	SystemManager												m_systemManager;
	std::unordered_map<int, std::unique_ptr<IComponentManager>>	m_componentManagers;
	EntityManager												m_entityManager;

public:
	template <typename ComponentType>
	ComponentManager<ComponentType>&	getComponentManager();
	IComponentManager*					getComponentManager(int componentId);
	EntityHandle						createEntity();
	void								destroyEntity(const Entity& entity);

	template <typename SystemType, typename... Args>
	void								createSystem(Args&&... args);

	template <typename SystemType, typename... Args>
	void								createDispatchingSystem(Args&&... args);

	SystemManager&						getSystemManager();
};
}

#include "World.tpp"
