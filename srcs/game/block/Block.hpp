#pragma once

#include "../../ecs/entity/Entity.hpp"

namespace game {

typedef unsigned int	BlockId;

struct Block {
	BlockId		type;
	ecs::Entity	entity = -1;

	Block();

	bool	hasEntity() const;
};
}
