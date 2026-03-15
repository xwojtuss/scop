#pragma once

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../game/world/ChunkManager.hpp"

namespace ecs {
class World;

class ChunkSystem : public ASystem {
private:
	game::world::ChunkManager	m_chunkManager;

public:
	ChunkSystem(ecs::World& world, render::IRenderer& renderer);
	~ChunkSystem() = default;

	void			onPlayerMove(const PlayerMoveEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
