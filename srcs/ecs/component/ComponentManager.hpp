#pragma once

#include <array>
#include <unordered_map>
#include <stdexcept>

#include "IComponentManager.hpp"
#include "../entity/Entity.hpp"

namespace ecs {
constexpr int	maxComponents = 2048;

template <typename ComponentType>
class ComponentManager : public IComponentManager {
private:
	std::array<ComponentType, maxComponents>	m_components;
	std::unordered_map<Entity, size_t>			m_entityToComponentIndex;
	std::size_t									m_componentCount;

public:
	ComponentManager();

	void				addComponent(const Entity& entity, const ComponentType& component);
	void				removeComponent(const Entity& entity) override;
	ComponentType*		getComponent(const Entity& entity);
	void				getComponent(const Entity& entity, IComponent*& component) override;
	bool				hasComponent(const Entity& entity) const override;
	size_t				getComponentCount() const;
	ComponentType*		getComponentAtIndex(size_t index);

	ComponentManager&	operator=(const ComponentManager& other);
};
}

#include "ComponentManager.tpp"
