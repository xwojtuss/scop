#include "ChunkLoader.hpp"

using namespace game::world;

Chunk&	ChunkLoader::loadChunk(unsigned short x, unsigned short y, unsigned short z) {
	Chunk* chunk;

	chunk = m_earthGenerator.generateChunk(x, y, z);
	if (!chunk)
		throw std::runtime_error("Failed to generate chunk");
	return *chunk;
}

void	ChunkLoader::saveChunk(unsigned short x, unsigned short y, unsigned short z) {
	(void)x;
	(void)y;
	(void)z;
}