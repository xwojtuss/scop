#include "EarthGenerator.hpp"

#include <algorithm>

using namespace game::world;

EarthGenerator::EarthGenerator() : m_heightMap(16, 16, 4, 0.01f) {
}

void	EarthGenerator::generateChunk(Chunk* chunk, glm::ivec3 chunkPosition) {
	const int worldChunkBaseY = static_cast<int>(chunkPosition.y) * chunkYSize;
	const int maxTerrainHeight = std::min<int>(scene::worldinfo::terrainMaxHeightBlocks, chunkYSize * scene::worldinfo::maxVerticalRenderDistance);
	int worldX, worldY, worldZ, terrainHeight;


	for (unsigned short blockX = 0; blockX < chunkXSize; ++blockX) {
		for (unsigned short blockZ = 0; blockZ < chunkZSize; ++blockZ) {
			worldX = static_cast<int>(chunkPosition.x) * chunkXSize + static_cast<int>(blockX);
			worldZ = static_cast<int>(chunkPosition.z) * chunkZSize + static_cast<int>(blockZ);

			terrainHeight = static_cast<int>(m_heightMap.getNormalizedValue(worldX, worldZ) * maxTerrainHeight);

			for (unsigned short blockY = 0; blockY < chunkYSize; ++blockY) {
				worldY = worldChunkBaseY + blockY;

				if (worldY < terrainHeight)
					chunk->setBlock(blockX, blockY, blockZ, game::Block(1));
			}
		}
	}
}
