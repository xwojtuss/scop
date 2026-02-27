#include "TickingMessageSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

TickingMessageSystem::TickingMessageSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<Message>();
}

void	TickingMessageSystem::onTick(const TickEvent& event) {
	(void)event;

	for (const Entity& entity : m_entities) {
		Message* message = m_world->getComponentManager<Message>().getComponent(entity);
		if (message) {
			std::cout << "Entity " << entity << ": " << message->message << std::endl;
		}
	}
}

void	TickingMessageSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<TickEvent>(this, &TickingMessageSystem::onTick);
}
