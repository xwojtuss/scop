#pragma once

#include "Chunk.hpp"
#include "ChunkMesher.hpp"
#include "ChunkLoader.hpp"
#include "../../ecs/World.hpp"
#include "../../ecs/entity/EntityHandle.hpp"
#include "../../ecs/component/Components.hpp"
#include "../../render/IRenderer.hpp"
#include "../../ecs/system/types/RenderSystem.hpp"

namespace game::world {
constexpr unsigned short	maxHorizontalRenderDistance = 8;
constexpr unsigned short	maxVerticalRenderDistance = 4;
class ChunkManager {
private:
	std::vector<Chunk>			m_chunks;
	ChunkMesher					m_chunkMesher;
	// ChunkLoader					m_chunkLoader;
	game::block::BlockDatas&	m_blockDatas;

public:
	ChunkManager(game::block::BlockDatas& blockDatas);
	~ChunkManager() = default;

	void	createChunkEntities(ecs::World& world, render::IRenderer& renderer);
};
}
