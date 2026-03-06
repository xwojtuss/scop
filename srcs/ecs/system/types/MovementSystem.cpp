#include "MovementSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

MovementSystem::MovementSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform>();
	m_dependencies.addDependency<component::Velocity>();
}
#include <iostream>
void	MovementSystem::onSimulate(const SimulateEvent& event) {
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

void	MovementSystem::onInput(const InputEvent& event) {
	(void)event;

	for (const Entity& entity : m_entities) {
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);

		if (!velocity || !transform)
			continue;

		component::Input* input = m_world->getComponentManager<component::Input>().getComponent(entity);

		velocity->desiredVelocity = transform->forward() * input->command.moveForward + transform->right() * input->command.moveRight + ftm::vec3(0,1,0) * input->command.moveUp;
		if (input && transform->canRotate) {
			float angleX = input->command.lookUp * input->mouseSensitivity;
			float angleY = input->command.lookRight * input->mouseSensitivity;

			float pitch = std::asin(ftm::clamp(transform->forward()[1], -1.0f, 1.0f));
			float clampedDelta = ftm::clamp(pitch + angleX, -input->command.maxPitch, input->command.maxPitch) - pitch;
			
			if (clampedDelta > input->command.maxPitch) clampedDelta = input->command.maxPitch;
			else if (clampedDelta < -input->command.maxPitch) clampedDelta = -input->command.maxPitch;
			
			ftm::quat rotX = ftm::angleAxis(clampedDelta, transform->right());
			ftm::quat rotY = ftm::angleAxis(angleY, scene::worldinfo::up);
			transform->rotation = ftm::normalize(rotY * rotX * transform->rotation);
		}
	}
}

void	MovementSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &MovementSystem::onSimulate);
	dispatcher.subscribe(this, &MovementSystem::onInput);
}
