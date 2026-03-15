#include "ChunkSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

ChunkSystem::ChunkSystem(ecs::World& world, render::IRenderer& renderer) : ASystem(Dependencies()), m_chunkManager(game::world::ChunkManager(world.getBlockDatas(), world, renderer)) {
}

void ChunkSystem::onPlayerMove(const PlayerMoveEvent& event) {
	(void)event;
}

void	ChunkSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &ChunkSystem::onPlayerMove);
}
