#include "ChunkLoader.hpp"

using namespace game::world;

Chunk&	ChunkLoader::loadChunk(int x, int y, int z) {
	Chunk* chunk;

	chunk = m_earthGenerator.generateChunk(x, y, z);
	if (!chunk)
		throw std::runtime_error("Failed to generate chunk");
	return *chunk;
}

void	ChunkLoader::saveChunk(int x, int y, int z) {
	(void)x;
	(void)y;
	(void)z;
}