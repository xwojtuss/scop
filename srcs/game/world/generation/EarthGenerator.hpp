#pragma once

#include <random>

#include "Perlin2DMap.hpp"
#include "../Chunk.hpp"
#include "../../../scene/WorldInfo.hpp"

namespace game::world {
class EarthGenerator {
private:
	Perlin2DMap	m_heightMap;

public:
	EarthGenerator();
	~EarthGenerator() = default;

	Chunk*	generateChunk(unsigned short x, unsigned short y, unsigned short z);
};
}
