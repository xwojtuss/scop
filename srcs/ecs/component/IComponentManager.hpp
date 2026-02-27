#pragma once

#include "../entity/Entity.hpp"

namespace ecs {
class IComponentManager {
public:
	virtual ~IComponentManager() = default;

	virtual void			removeComponent(const Entity& entity) = 0;
	virtual bool			hasComponent(const Entity& entity) const = 0;
};
}
