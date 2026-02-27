#pragma once

#include "../ASystem.hpp"
#include "../Dispatcher.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../render/input/InputTypes.hpp"
#include "../../../render/input/InputManager.hpp"

namespace ecs {
class PlayerInputSystem : public ASystem {
private:
	render::input::InputManager&	m_inputManager;
	Dispatcher&						m_dispatcher;

public:
	PlayerInputSystem(render::input::InputManager& inputManager, Dispatcher& dispatcher);

	void			onSimulate(const SimulateEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
