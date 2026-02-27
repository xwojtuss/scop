#pragma once

#include <memory>
#include <vector>

#include "component/IComponentManager.hpp"
#include "component/ComponentManager.hpp"
#include "entity/EntityManager.hpp"
#include "system/SystemManager.hpp"

namespace ecs {
struct EntityHandle;

class World {
private:
	SystemManager									m_systemManager;
	std::vector<std::unique_ptr<IComponentManager>>	m_componentManagers;
	EntityManager									m_entityManager;

public:
	template <typename ComponentType>
	ComponentManager<ComponentType>&	getComponentManager();
	IComponentManager*					getComponentManager(int componentId);
	EntityHandle						createEntity();
	void								destroyEntity(const Entity& entity);

	template <typename SystemType>
	void								createSystem();	
	SystemManager&						getSystemManager();};
}

#include "World.tpp"
