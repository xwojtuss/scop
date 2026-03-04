#pragma once

#include <limits>

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"

namespace ecs {
class SimpleAnimationSystem : public ASystem {
public:
	SimpleAnimationSystem();

	void			onSimulate(const SimulateEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
