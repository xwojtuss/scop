#pragma once

#include <string>
#include <iostream>

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Component.hpp"

namespace ecs {
class World;

class TickingMessageSystem : public ASystem {
public:
	TickingMessageSystem();
	~TickingMessageSystem() = default;

	void					onTick(const TickEvent& event);
	virtual void			bindEvents(Dispatcher& dispatcher) override;
};
}
