#include "ArrowMovementSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

ArrowMovementSystem::ArrowMovementSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform>();
	m_dependencies.addDependency<component::Velocity>();
}

void	ArrowMovementSystem::onSimulate(const SimulateEvent& event) {
	float speed = 0.0f;

	for (const Entity& entity : m_entities) {
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		
		if (!transform || !velocity || !velocity->canMove)
			continue;

		if (std::abs(ftm::length(velocity->desiredVelocity)) > 0.0f) {
			ftm::vec3 direction = ftm::normalize(velocity->desiredVelocity);

			velocity->velocity += direction * velocity->acceleration * event.deltaTime;

			if (ftm::length(velocity->velocity) > velocity->maxSpeed)
				velocity->velocity = ftm::normalize(velocity->velocity) * velocity->maxSpeed;
		} else if ((speed = ftm::length(velocity->velocity)) > 0.0f) {
			speed = std::max(0.0f, speed - velocity->decelleration * event.deltaTime);
			velocity->velocity = (speed > 0.0f) ? ftm::normalize(velocity->velocity) * speed : ftm::vec3(0.0f);
		}
		transform->position += velocity->velocity * event.deltaTime;
	}
}

void	ArrowMovementSystem::onInput(const InputEvent& event) {
	(void)event;

	for (const Entity& entity : m_entities) {
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);

		if (!velocity || !transform)
			continue;

		velocity->desiredVelocity = ftm::vec3(0.0f);

		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveForward))
			velocity->desiredVelocity += scene::worldinfo::forward;
		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveBackward))
			velocity->desiredVelocity += scene::worldinfo::backward;
		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveRight))
			velocity->desiredVelocity += scene::worldinfo::right;
		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveLeft))
			velocity->desiredVelocity += scene::worldinfo::left;
		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveUp))
			velocity->desiredVelocity += scene::worldinfo::up;
		if (render::input::hasEvent(event.command.activeEvents, render::input::InputEvent::ArrowMoveDown))
			velocity->desiredVelocity += scene::worldinfo::down;
	}
}

void	ArrowMovementSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &ArrowMovementSystem::onSimulate);
	dispatcher.subscribe(this, &ArrowMovementSystem::onInput);
}
