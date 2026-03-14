#include "Block.hpp"

using namespace game;

Block::Block() : id(0), entity(-1) {}

Block::Block(BlockId id) : id(id), entity(-1) {}

bool	Block::hasEntity() const {
	return entity != -1;
}
