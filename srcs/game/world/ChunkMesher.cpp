#include "ChunkMesher.hpp"

using namespace game::world;

ChunkMesher::ChunkMesher(game::block::BlockDatas& blockDatas) : m_blockDatas(blockDatas) {
}

/**
 * Lots of room for improvement here.
 * Right now the stupidest solution was used just to get something working
 * @todo TODO: optimize
 */
assets::MeshData	ChunkMesher::toMeshData(const Chunk& chunk) {
	assets::MeshData meshData;

	for (int x = 0; x < chunkXSize; ++x) {
		for (int y = 0; y < chunkYSize; ++y) {
			for (int z = 0; z < chunkZSize; ++z) {
				const game::Block& block = chunk.getBlock(x, y, z);

				if (block.id < 1)
					continue;

				const game::block::BlockData& blockData = m_blockDatas.getBlockData(block.id);

				for (const auto& vertex : blockData.meshData.vertices) {
					meshData.vertices.push_back({
						vertex.pos + glm::vec3(x, y, z),
						vertex.color,
						vertex.texCoord
					});
				}

				for (const auto& index : blockData.meshData.indices) {
					meshData.indices.push_back(static_cast<uint32_t>(meshData.vertices.size() - blockData.meshData.vertices.size() + index));
				}
			}
		}
	}

	return meshData;
}
