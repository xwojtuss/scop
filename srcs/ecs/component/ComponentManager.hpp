#pragma once

#include <array>
#include <unordered_map>
#include <stdexcept>

#include "IComponentManager.hpp"
#include "../entity/Entity.hpp"

namespace ecs {
constexpr int	maxComponents = 512;

template <typename ComponentType>
class ComponentManager : public IComponentManager {
private:
	std::array<ComponentType, maxComponents>	m_components;
	std::unordered_map<Entity, size_t>			m_entityToComponentIndex;
	std::array<Entity, maxComponents>			m_componentIndexToEntity;
	std::size_t									m_componentCount;

public:
	ComponentManager();

	void	addComponent(const Entity& entity, const ComponentType& component);
	void	removeComponent(const Entity& entity);
	ComponentType*	getComponent(const Entity& entity) {
		auto it = m_entityToComponentIndex.find(entity);
		if (it == m_entityToComponentIndex.end())
			return nullptr;
		return &m_components[it->second];
	}

	bool	hasComponent(const Entity& entity) const {
		return m_entityToComponentIndex.find(entity) != m_entityToComponentIndex.end();
	}

	ComponentManager& operator=(const ComponentManager& other);
};
}

#include "ComponentManager.tpp"
