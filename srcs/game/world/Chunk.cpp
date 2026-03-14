#include "Chunk.hpp"

using namespace game::world;

Chunk::Chunk() {
	std::memset(m_blocks, 0, sizeof(m_blocks));
}

game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) {
	return m_blocks[x][y][z];
}

const game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) const {
	return m_blocks[x][y][z];
}

glm::ivec3	Chunk::getBlockPosition(unsigned short x, unsigned short y, unsigned short z) const {
	return m_chunkPosition * glm::ivec3(chunkXSize, chunkYSize, chunkZSize) + glm::ivec3(x, y, z);
}

glm::ivec3	Chunk::getChunkPosition() const {
	return m_chunkPosition;
}

void	Chunk::setBlock(unsigned short x, unsigned short y, unsigned short z, const game::Block& block) {
	m_blocks[x][y][z] = block;
}

void	Chunk::removeBlock(unsigned short x, unsigned short y, unsigned short z) {
	m_blocks[x][y][z] = game::Block();
}
