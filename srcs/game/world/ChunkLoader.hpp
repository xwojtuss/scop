#pragma once

#include "generation/EarthGenerator.hpp"

#include <memory>
#include <stdexcept>

namespace game::world {
class ChunkLoader {
private:
	EarthGenerator	m_earthGenerator;

public:
	ChunkLoader() = default;
	~ChunkLoader() = default;

	std::unique_ptr<Chunk>	loadChunk(glm::ivec3 chunkPosition);
	void					saveChunk(glm::ivec3 chunkPosition);
};
}
