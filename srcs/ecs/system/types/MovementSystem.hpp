#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"

namespace ecs {
class World;

class MovementSystem : public ASystem {
public:
	MovementSystem();
	~MovementSystem() = default;

	void					onInput(const InputEvent& event);
	void					onSimulate(const SimulateEvent& event);
	virtual void			bindEvents(Dispatcher& dispatcher) override;
};
}
