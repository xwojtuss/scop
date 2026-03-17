#include "Chunk.hpp"

using namespace game::world;

game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) {
	return m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z];
}

const game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) const {
	return m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z];
}

void	Chunk::setBlock(unsigned short x, unsigned short y, unsigned short z, const game::Block& block) {
	m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z] = block;
}

void	Chunk::removeBlock(unsigned short x, unsigned short y, unsigned short z) {
	m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z] = game::Block();
}

