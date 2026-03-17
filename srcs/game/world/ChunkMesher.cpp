#include "ChunkMesher.hpp"

#include <cmath>
#include <glm/geometric.hpp>

using namespace game::world;

ChunkMesher::ChunkMesher(game::block::BlockDatas& blockDatas) : m_blockDatas(blockDatas) {
}

/**
 * A bit of room for improvement here.
 * Meshes a chunk into a single mesh, can be optimized by checking chunk borders.
 * @todo TODO: optimize
 */
assets::MeshData	ChunkMesher::toMeshData(const Chunk& chunk) {
	assets::MeshData meshData;
	meshData.vertices.reserve(chunkXSize * chunkYSize * chunkZSize * 24);
	meshData.indices.reserve(chunkXSize * chunkYSize * chunkZSize * 36);

	for (int x = 0; x < chunkXSize; ++x) {
		for (int y = 0; y < chunkYSize; ++y) {
			for (int z = 0; z < chunkZSize; ++z) {
				const game::Block& block = chunk.getBlock(x, y, z);
				if (block.id == 0)
					continue;

				const assets::MeshData& blockMesh = m_blockDatas.getBlockData(block.id).meshData;
				if (blockMesh.indices.size() < 3 || blockMesh.vertices.empty())
					continue;

				for (size_t i = 0; i + 2 < blockMesh.indices.size(); i += 3) {
					const uint32_t i0 = blockMesh.indices[i];
					const uint32_t i1 = blockMesh.indices[i + 1];
					const uint32_t i2 = blockMesh.indices[i + 2];

					if (i0 >= blockMesh.vertices.size() || i1 >= blockMesh.vertices.size() || i2 >= blockMesh.vertices.size())
						continue;

					const render::Vertex& v0 = blockMesh.vertices[i0];
					const render::Vertex& v1 = blockMesh.vertices[i1];
					const render::Vertex& v2 = blockMesh.vertices[i2];

					const glm::vec3 edgeA = v1.pos - v0.pos;
					const glm::vec3 edgeB = v2.pos - v0.pos;
					const glm::vec3 normal = glm::cross(edgeA, edgeB);
					const float normalLength = glm::length(normal);

					if (normalLength <= std::numeric_limits<float>::epsilon())
						continue;

					const glm::vec3 n = glm::normalize(normal);
					const glm::vec3 absN = glm::abs(n);

					glm::ivec3 offset(0);
					if (glm::max(absN.x, glm::max(absN.y, absN.z)) == absN.x)
						offset.x = n.x > 0.0f ? 1 : -1;
					else if (glm::max(absN.x, glm::max(absN.y, absN.z)) == absN.y)
						offset.y = n.y > 0.0f ? 1 : -1;
					else
						offset.z = n.z > 0.0f ? 1 : -1;

					if (getVoxelCheckBounds(chunk, x + offset.x, y + offset.y, z + offset.z) != 0)
						continue;

					meshData.vertices.push_back({
						v0.pos + glm::vec3(x, y, z),
						v0.color,
						v0.texCoord
					});
					meshData.vertices.push_back({
						v1.pos + glm::vec3(x, y, z),
						v1.color,
						v1.texCoord
					});
					meshData.vertices.push_back({
						v2.pos + glm::vec3(x, y, z),
						v2.color,
						v2.texCoord
					});

					meshData.indices.push_back(static_cast<uint32_t>(meshData.vertices.size()) - 3);
					meshData.indices.push_back(static_cast<uint32_t>(meshData.vertices.size()) - 2);
					meshData.indices.push_back(static_cast<uint32_t>(meshData.vertices.size()) - 1);
				}
			}
		}
	}

	return meshData;
}

game::BlockId	ChunkMesher::getVoxelCheckBounds(const Chunk& chunk, int x, int y, int z) {
	if (x < 0 || x >= chunkXSize || y < 0 || y >= chunkYSize || z < 0 || z >= chunkZSize)
		return 0;
	return chunk.getBlock(x, y, z).id;
}