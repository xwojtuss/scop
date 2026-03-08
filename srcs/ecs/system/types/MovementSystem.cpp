#include "MovementSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

MovementSystem::MovementSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform>();
	m_dependencies.addDependency<component::Velocity>();
	m_dependencies.addDependency<component::Input>();
}

void	MovementSystem::onSimulate(const SimulateEvent& event) {
	float speed = 0.0f;

	for (const Entity& entity : m_entities) {
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
		component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(entity);
		
		if (!transform || !velocity || !velocity->canMove)
			continue;


		if (std::abs(glm::length(velocity->desiredVelocity)) > 0.0f) {
			glm::vec3 direction = glm::normalize(velocity->desiredVelocity);

			velocity->velocity += direction * velocity->acceleration * event.deltaTime;

			if (glm::length(velocity->velocity) > velocity->maxSpeed)
				velocity->velocity = glm::normalize(velocity->velocity) * velocity->maxSpeed;
		} else if ((speed = glm::length(velocity->velocity)) > 0.0f) {
			speed = std::max(0.0f, speed - velocity->decelleration * event.deltaTime);
			velocity->velocity = (speed > 0.0f) ? glm::normalize(velocity->velocity) * speed : glm::vec3(0.0f);
		}
		transform->position += velocity->velocity * event.deltaTime;
	}
}

void	MovementSystem::onInput(const InputEvent& event) {
	(void)event;

	if (!hasEntity(event.source))
		return;

	component::Velocity* velocity = m_world->getComponentManager<component::Velocity>().getComponent(event.source);
	component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(event.source);
	component::Input* input = m_world->getComponentManager<component::Input>().getComponent(event.source);

	if (!velocity || !transform || !input)
		return;

	velocity->desiredVelocity = transform->forward() * event.command.moveForward + transform->right() * event.command.moveRight + glm::vec3(0,1,0) * event.command.moveUp;
	if (transform->canRotate) {
		float angleX = event.command.lookUp * input->mouseSensitivity;
		float angleY = event.command.lookRight * input->mouseSensitivity;

		float pitch = std::asin(glm::clamp(transform->forward().y, -1.0f, 1.0f));
		float clampedDelta = glm::clamp(pitch + angleX, -event.command.maxPitch, event.command.maxPitch) - pitch;
		
		if (clampedDelta > event.command.maxPitch) clampedDelta = event.command.maxPitch;
		else if (clampedDelta < -event.command.maxPitch) clampedDelta = -event.command.maxPitch;
		
		glm::quat rotX = glm::angleAxis(clampedDelta, transform->right());
		glm::quat rotY = glm::angleAxis(angleY, scene::worldinfo::up);
		transform->rotation = glm::normalize(rotY * rotX * transform->rotation);
	}
}

void	MovementSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &MovementSystem::onSimulate);
	dispatcher.subscribe(this, &MovementSystem::onInput);
}
