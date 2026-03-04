#pragma once

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"

namespace ecs {
class ToggleShaderSystem : public ASystem {
public:
	ToggleShaderSystem();

	void			onInput(const InputEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
