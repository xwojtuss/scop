#include "ChunkManager.hpp"

using namespace game::world;

ChunkManager::ChunkManager(game::block::BlockDatas& blockDatas) : m_chunkMesher(blockDatas), m_blockDatas(blockDatas) {
	for (unsigned short x = 0; x < scene::worldinfo::maxHorizontalRenderDistance; ++x) {
		for (unsigned short z = 0; z < scene::worldinfo::maxHorizontalRenderDistance; ++z) {
			for (unsigned short y = 0; y < scene::worldinfo::maxVerticalRenderDistance; ++y) {
				m_chunks.push_back(&m_chunkLoader.loadChunk(x, y, z));
			}
		}
	}
}

void	ChunkManager::createChunkEntities(ecs::World& world, render::IRenderer& renderer) {
	const assets::TextureHandle sharedChunkTexture = renderer.createTexture(m_blockDatas.getBlockData(1).textureData);

	for (const auto& chunk : m_chunks) {
		const assets::MeshData meshData = m_chunkMesher.toMeshData(*chunk);
		if (meshData.vertices.empty() || meshData.indices.empty())
			continue;

		ecs::EntityHandle chunkEntity = world.createEntity();
		ecs::component::Mesh meshComponent;
		ecs::component::Texture textureComponent;
		ecs::component::Transform positionComponent;

		meshComponent.mesh = renderer.createMesh(meshData);
		meshComponent.pipelineType = assets::PipelineType::Textured;
		textureComponent.texture = sharedChunkTexture;
		positionComponent.position = glm::vec3(chunk->getChunkPosition() * glm::ivec3(chunkXSize, chunkYSize, chunkZSize));

		chunkEntity.addComponent(meshComponent);
		chunkEntity.addComponent(textureComponent);
		chunkEntity.addComponent(positionComponent);

		chunkEntity.registerToSystem<ecs::RenderSystem>();
	}
}

ChunkManager::~ChunkManager() {
	for (auto chunk : m_chunks) {
		delete chunk;
	}
}
