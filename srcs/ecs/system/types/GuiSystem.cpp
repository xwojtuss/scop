#include "GuiSystem.hpp"
#include "../../World.hpp"
#include "../../../render/gui/DebugPanel.hpp"

using namespace ecs;

GuiSystem::GuiSystem(render::gui::IGui& gui) : ASystem(Dependencies()), m_gui(gui) {
}

void	GuiSystem::onWorldReady(const WorldReadyEvent& event) {
	(void)event;

	render::gui::DebugPanel debugPanel(m_gui, *m_world);
	registerPanel(render::input::DebugMenuToggle, debugPanel);
}

void	GuiSystem::onInput(const InputEvent& event) {
	for (const auto& [inputEvent, panelType] : m_eventToPanelType) {
		if (!render::input::hasEvent(event.command.startedEvents, inputEvent))
			continue;

		auto it = m_panels.find(panelType);
		if (it == m_panels.end())
			continue;
		it->second->setCaller(event.source);
		it->second->toggle();
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
	dispatcher.subscribe<WorldReadyEvent>(this, &GuiSystem::onWorldReady);
}
