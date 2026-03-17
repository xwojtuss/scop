#pragma once

#include "../../ecs/entity/Entity.hpp"

namespace game {

typedef unsigned int	BlockId;

struct Block {
	BlockId		id;
	ecs::Entity	entity = -1;

	Block();
	Block(BlockId id);

	bool	hasEntity() const;
};
}
