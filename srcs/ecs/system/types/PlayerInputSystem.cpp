#include "PlayerInputSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

PlayerInputSystem::PlayerInputSystem(render::input::InputManager& inputManager, Dispatcher& dispatcher) : ASystem(Dependencies()), m_inputManager(inputManager), m_dispatcher(dispatcher) {
	m_dependencies.addDependency<component::Input>();
}

void	PlayerInputSystem::onSimulate(const SimulateEvent& event) {
	render::input::InputCommand command = m_inputManager.buildCommand();
	ecs::InputEvent inputEvent{};

	(void)event;
	for (const Entity& entity : m_entities) {
		component::Input* input = m_world->getComponentManager<component::Input>().getComponent(entity);

		if (!input)
			continue;

		input->command = command;
	}
	
	m_dispatcher.emit<ecs::InputEvent>(inputEvent);
}

void	PlayerInputSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<SimulateEvent>(this, &PlayerInputSystem::onSimulate);
}
