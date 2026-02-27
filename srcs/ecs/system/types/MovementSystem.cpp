#include "MovementSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

MovementSystem::MovementSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform>();
	m_dependencies.addDependency<component::Velocity>();
}

void	MovementSystem::onSimulate(const SimulateEvent& event) {
	for (const Entity& entity : m_entities) {
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		
		if (!transform || !velocity)
			continue;

		glm::vec3 delta = velocity->desiredVelocity - velocity->velocity;
	
		float multiplier = ((glm::length2(velocity->desiredVelocity) > 0.0f) ? velocity->acceleration * event.deltaTime : scene::worldinfo::drag * event.deltaTime);
		velocity->velocity += delta * multiplier;

		if (glm::length(velocity->velocity) > velocity->maxSpeed)
			velocity->velocity = glm::normalize(velocity->velocity) * velocity->maxSpeed;

		transform->position += velocity->velocity * event.deltaTime;
	}
}

void	MovementSystem::onInput(const InputEvent& event) {
	(void)event;

	for (const Entity& entity : m_entities) {
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);

		if (!velocity || !transform)
			continue;

		component::Input* input = m_world->getComponentManager<component::Input>().getComponent(entity);
		if (input) {
			velocity->desiredVelocity = glm::vec3(input->command.moveRight, input->command.moveUp, -input->command.moveForward) * velocity->maxSpeed;
		}
	}
}

void	MovementSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &MovementSystem::onSimulate);
	dispatcher.subscribe(this, &MovementSystem::onInput);
}
