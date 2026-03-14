#include "ChunkManager.hpp"

using namespace game::world;

ChunkManager::ChunkManager(game::block::BlockDatas& blockDatas) : m_chunkMesher(blockDatas), m_blockDatas(blockDatas) {
	Chunk chunk(0, 0, 0);
	chunk.setBlock(0, 1, 0, game::Block(1));
	chunk.setBlock(0, 3, 0, game::Block(1));
	chunk.setBlock(0, 5, 0, game::Block(1));
	chunk.setBlock(1, 1, 0, game::Block(1));
	chunk.setBlock(1, 3, 0, game::Block(1));
	chunk.setBlock(1, 5, 0, game::Block(1));
	chunk.setBlock(3, 5, 0, game::Block(1));
	chunk.setBlock(3, 6, 0, game::Block(1));
	chunk.setBlock(3, 5, 1, game::Block(1));
	chunk.setBlock(3, 6, 1, game::Block(1));

	m_chunks.push_back(chunk);

	chunk.setChunkPosition(1, 0, 0);
	m_chunks.push_back(chunk);
}

void	ChunkManager::createChunkEntities(ecs::World& world, render::IRenderer& renderer) {
	const assets::TextureHandle sharedChunkTexture = renderer.createTexture(m_blockDatas.getBlockData(1).textureData);

	for (const auto& chunk : m_chunks) {
		ecs::EntityHandle chunkEntity = world.createEntity();
		ecs::component::Mesh meshComponent;
		ecs::component::Texture textureComponent;
		ecs::component::Transform positionComponent;

		meshComponent.mesh = renderer.createMesh(m_chunkMesher.toMeshData(chunk));
		meshComponent.pipelineType = assets::PipelineType::Textured;
		textureComponent.texture = sharedChunkTexture;
		positionComponent.position = glm::vec3(chunk.getChunkPosition() * glm::ivec3(chunkXSize, chunkYSize, chunkZSize));

		chunkEntity.addComponent(meshComponent);
		chunkEntity.addComponent(textureComponent);
		chunkEntity.addComponent(positionComponent);

		chunkEntity.registerToSystem<ecs::RenderSystem>();
	}
}
