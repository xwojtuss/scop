#include "ChunkLoader.hpp"

using namespace game::world;

std::unique_ptr<Chunk>	ChunkLoader::loadChunk(glm::ivec3 chunkPosition) {
	Chunk* chunk = new Chunk();

	m_earthGenerator.generateChunk(chunk, chunkPosition);
	if (!chunk)
		throw std::runtime_error("Failed to generate chunk");
	return std::unique_ptr<Chunk>(chunk);
}

void	ChunkLoader::saveChunk(glm::ivec3 chunkPosition) {
	(void)chunkPosition;
}
