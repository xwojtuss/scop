#pragma once

#include "Chunk.hpp"
#include "../block/BlockData.hpp"
#include "../../assets/Resources.hpp"

namespace game::world {
class ChunkMesher {
private:
	game::block::BlockDatas&	m_blockDatas;

	static game::BlockId	getVoxelCheckBounds(const Chunk& chunk, int x, int y, int z);

public:
	ChunkMesher(game::block::BlockDatas& blockDatas);

	assets::MeshData	toMeshData(const Chunk& chunk);
};
}
