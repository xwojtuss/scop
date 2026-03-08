#include "EventsRuntimePanel.hpp"

using namespace render::gui;

EventsRuntimePanel::EventsRuntimePanel(IGui& gui, ecs::Dispatcher& dispatcher) : APanel(gui), m_dispatcher(dispatcher) {
}

void	EventsRuntimePanel::display() {
	if (!m_isOpen)
		return;

	std::stringstream ss;
	auto runtimes = m_dispatcher.getEventRuntimes();
	bool first = true;

	if (m_gui.beginWindow("EventsRuntime", &m_isOpen)) {
		for (const auto& [eventName, runtime] : runtimes) {
			if (!first)
				m_gui.separator();
			
			first = false;
			
			ss << std::fixed << std::setprecision(7);
			ss << eventName << " Runtime: " << runtime.count() << " ms";
			m_gui.text(ss.str());
			ss.str("");
		}
	}
	m_gui.endWindow();
}
