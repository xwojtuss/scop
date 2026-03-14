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

	Chunk&	loadChunk(unsigned short x, unsigned short y, unsigned short z);
	void	saveChunk(unsigned short x, unsigned short y, unsigned short z);
};
}
