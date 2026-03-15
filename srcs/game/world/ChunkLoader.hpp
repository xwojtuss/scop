#pragma once

#include "generation/EarthGenerator.hpp"

#include <stdexcept>

namespace game::world {
class ChunkLoader {
private:
	EarthGenerator	m_earthGenerator;

public:
	ChunkLoader() = default;
	~ChunkLoader() = default;

	Chunk&	loadChunk(int x, int y, int z);
	void	saveChunk(int x, int y, int z);
};
}
