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

		if (!transform || !animation || event.time <= std::numeric_limits<float>::epsilon())
			continue;

		switch (animation->type) {
		case component::AnimationType::Spin:
			transform->rotation = ftm::rotate(transform->rotation, ftm::radians(90.0f) * animation->speed * event.deltaTime, scene::worldinfo::up);
			break;
		case component::AnimationType::Bounce:
			transform->position[1] += std::sin(event.time * animation->speed * 2.0f) * event.deltaTime * 0.5f * animation->intensity;
			break;
		case component::AnimationType::Jitter:
			transform->position[0] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * animation->speed * animation->intensity;
			transform->position[1] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * animation->speed * animation->intensity;
			transform->position[2] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * animation->speed * animation->intensity;
			break;
		case component::AnimationType::Random:
			transform->position[0] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f * animation->intensity;
			transform->position[1] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f * animation->intensity;
			transform->position[2] += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 2.0f * animation->intensity;
			transform->rotation = ftm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ftm::radians(180.0f) * animation->intensity * event.deltaTime, scene::worldinfo::up);
			transform->rotation = ftm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ftm::radians(180.0f) * animation->intensity * event.deltaTime, scene::worldinfo::right);
			transform->rotation = ftm::rotate(transform->rotation, (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ftm::radians(180.0f) * animation->intensity * event.deltaTime, scene::worldinfo::forward);
			transform->scale += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * event.deltaTime * 1.0f * animation->intensity;
			break;
		case component::AnimationType::Circle:
			transform->position[0] = std::cos(event.time * animation->speed) * 2.0f * animation->intensity;
			transform->position[2] = std::sin(event.time * animation->speed) * 2.0f * animation->intensity;
			break;
		case component::AnimationType::Pulse:
			transform->scale = ftm::vec3(std::sin(event.time * animation->speed) * animation->intensity + animation->intensity);
			break;
		}
	}
}

void	SimpleAnimationSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<SimulateEvent>(this, &SimpleAnimationSystem::onSimulate);
}
