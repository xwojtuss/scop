#pragma once

#include <string>

#include "ftm/ftm.hpp"
#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"

namespace ecs {
class World;

class ArrowMovementSystem : public ASystem {
public:
	ArrowMovementSystem();
	~ArrowMovementSystem() = default;

	void					onInput(const InputEvent& event);
	void					onSimulate(const SimulateEvent& event);
	virtual void			bindEvents(Dispatcher& dispatcher) override;
};
}
