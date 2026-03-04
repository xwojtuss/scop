#include "SimpleAnimationSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

SimpleAnimationSystem::SimpleAnimationSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform>();
	m_dependencies.addDependency<component::Animation>();
}

void	SimpleAnimationSystem::onSimulate(const SimulateEvent& event) {
	for (const Entity& entity : m_entities) {
		component::Transform* transform = m_world->getComponentManager<component::Transform>().getComponent(entity);
		const component::Animation* animation = m_world->getComponentManager<component::Animation>().getComponent(entity);

		if (!transform || !animation)
			continue;

		switch (animation->type) {
		case component::AnimationType::Spin:
			transform->rotation = glm::rotate(transform->rotation, glm::radians(90.0f) * animation->speed * event.deltaTime, scene::worldinfo::up);
			break;
		case component::AnimationType::Bounce:
			transform->position.y += std::sin(event.time * animation->speed * 2.0f) * event.deltaTime * 0.5f;
			break;
		case component::AnimationType::Jitter:
			transform->position.y += std::sin(event.time * animation->speed * 200.0f) * event.deltaTime * 2.0f;
			transform->position.x += std::cos(event.time * animation->speed * 200.0f) * event.deltaTime * 2.0f;
			transform->position.z += std::sin(event.time * animation->speed * 200.0f) * event.deltaTime * 2.0f;
			break;
		case component::AnimationType::Random:
			transform->position.x += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f;
			transform->position.y += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f;
			transform->position.z += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f;
			transform->rotation = glm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * glm::radians(180.0f) * event.deltaTime, scene::worldinfo::up);
			transform->rotation = glm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * glm::radians(180.0f) * event.deltaTime, scene::worldinfo::right);
			transform->rotation = glm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * glm::radians(180.0f) * event.deltaTime, scene::worldinfo::forward);
			transform->scale += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 1.0f;
			break;
		case component::AnimationType::Circle:
			transform->position.x = std::cos(event.time * animation->speed) * 2.0f;
			transform->position.z = std::sin(event.time * animation->speed) * 2.0f;
			break;
		}
	}
}

void	SimpleAnimationSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<SimulateEvent>(this, &SimpleAnimationSystem::onSimulate);
}
