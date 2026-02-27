#include "WindowControlSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

WindowControlSystem::WindowControlSystem(platform::window::IWindow& window) : ASystem(Dependencies()), m_window(window) {
	m_dependencies.addDependency<component::Input>();
}
#include <iostream>
void	WindowControlSystem::onInput(const InputEvent& event) {
	(void)event;

	for (const Entity& entity : m_entities) {
		component::Input* input = m_world->getComponentManager<component::Input>().getComponent(entity);

		if (!input)
			continue;

		if (!m_window.isMouseCursorVisible()
			&& render::input::hasEvent(input->command.startedEvents, render::input::InputEvent::ToggleCursor)) {
			m_window.setMouseCursorVisible(true);
			m_window.setMouseCursorPositionToCenter();
			
			component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
			if (transform) transform->canRotate = false;

			component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
			if (velocity) velocity->canMove = false;

		} else if (m_window.isMouseCursorVisible()
			&& render::input::hasAnyEvent(input->command.startedEvents, render::input::InputEvent::AnyMouseButton)) {
			m_window.setMouseCursorVisible(false);
			
			component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
			if (velocity) velocity->canMove = true;

			component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
			if (transform) transform->canRotate = true;
		}
	}
}

void	WindowControlSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<InputEvent>(this, &WindowControlSystem::onInput);
}
