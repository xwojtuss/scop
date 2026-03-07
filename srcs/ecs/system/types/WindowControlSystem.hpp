#pragma once

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../render/gui/IGui.hpp"
#include "../../../render/input/InputTypes.hpp"
#include "../../../render/input/InputManager.hpp"
#include "../../../platform/window/IWindow.hpp"

namespace ecs {
class WindowControlSystem : public ASystem {
private:
	platform::window::IWindow&	m_window;
	render::gui::IGui&			m_gui;

public:
	WindowControlSystem(platform::window::IWindow& window, render::gui::IGui& gui);

	void			onInput(const InputEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
