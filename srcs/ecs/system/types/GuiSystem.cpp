#include "GuiSystem.hpp"
#include "../../World.hpp"
#include "../../../render/gui/DebugPanel.hpp"

using namespace ecs;

GuiSystem::GuiSystem(render::gui::IGui& gui) : ASystem(Dependencies()), m_gui(gui), m_state() {

	registerPanel<render::gui::DebugPanel>(render::input::DebugMenuToggle);
}

void	GuiSystem::onInput(const InputEvent& event) {
	(void)event;

	auto& inputManager = m_world->getComponentManager<component::Input>();
	for (size_t i = 0; i < inputManager.getComponentCount(); ++i) {
		component::Input* input = inputManager.getComponentAtIndex(i);

		if (!input)
			continue;

		for (const auto& [inputEvent, panelType] : m_eventToPanelType) {
			if (!render::input::hasEvent(input->command.startedEvents, inputEvent))
				continue;

			auto it = m_panels.find(panelType);
			if (it != m_panels.end())
				it->second->toggle();
		}
	}
}

void	GuiSystem::onRendererFrame(const RendererFrameEvent& event) {
	m_gui.beginFrame();

	for (const auto& [type, panel] : m_panels) {
		if (panel && panel->isOpen())
			panel->display();
	}

	m_gui.endFrame();
	event.renderer->render(m_gui);
}

void	GuiSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<InputEvent>(this, &GuiSystem::onInput);
	dispatcher.subscribe<RendererFrameEvent>(this, &GuiSystem::onRendererFrame);
}