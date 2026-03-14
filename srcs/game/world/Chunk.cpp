#include "Chunk.hpp"

using namespace game::world;

Chunk::Chunk(unsigned short x, unsigned short y, unsigned short z) : m_chunkPosition(x, y, z) {
	m_blocks = new game::Block[chunkXSize * chunkYSize * chunkZSize]();
}

Chunk::Chunk(glm::ivec3 chunkPosition) : m_chunkPosition(chunkPosition) {
	m_blocks = new game::Block[chunkXSize * chunkYSize * chunkZSize]();
}

game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) {
	return m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z];
}

const game::Block&	Chunk::getBlock(unsigned short x, unsigned short y, unsigned short z) const {
	return m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z];
}

glm::ivec3	Chunk::getBlockPosition(unsigned short x, unsigned short y, unsigned short z) const {
	return m_chunkPosition * glm::ivec3(chunkXSize, chunkYSize, chunkZSize) + glm::ivec3(x, y, z);
}

glm::ivec3	Chunk::getChunkPosition() const {
	return m_chunkPosition;
}

void	Chunk::setChunkPosition(unsigned short x, unsigned short y, unsigned short z) {
	m_chunkPosition = glm::ivec3(x, y, z);
}

void	Chunk::setChunkPosition(glm::ivec3 chunkPosition) {
	m_chunkPosition = chunkPosition;
}

void	Chunk::setBlock(unsigned short x, unsigned short y, unsigned short z, const game::Block& block) {
	m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z] = block;
}

void	Chunk::removeBlock(unsigned short x, unsigned short y, unsigned short z) {
	m_blocks[x * chunkYSize * chunkZSize + y * chunkZSize + z] = game::Block();
}

Chunk::~Chunk() {
	delete[] m_blocks;
}
