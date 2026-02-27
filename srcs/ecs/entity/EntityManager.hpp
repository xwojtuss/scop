#pragma once

#include <array>

#include "Entity.hpp"

namespace ecs {
class EntityManager {
private:
	Entity	lastEntity;

public:
	EntityManager();
	~EntityManager() = default;

	Entity	createEntity();
};
}
