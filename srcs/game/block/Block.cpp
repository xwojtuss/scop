#include "Block.hpp"

using namespace game;

Block::Block() : type(0), entity(-1) {}

bool	Block::hasEntity() const {
	return entity != -1;
}
