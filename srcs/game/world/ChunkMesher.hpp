#pragma once

#include "Chunk.hpp"
#include "../block/BlockData.hpp"
#include "../../assets/Resources.hpp"

namespace game::world {
class ChunkMesher {
private:
	game::block::BlockDatas&	m_blockDatas;

public:
	ChunkMesher(game::block::BlockDatas& blockDatas);

	assets::MeshData	toMeshData(const Chunk& chunk);
};
}
