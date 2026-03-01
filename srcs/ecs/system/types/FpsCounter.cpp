#include "FpsCounter.hpp"
#include "../../World.hpp"

using namespace ecs;

FpsCounter::FpsCounter() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform2D>();
	m_dependencies.addDependency<component::Text>();
}

void	FpsCounter::onRender(const RenderEvent& event) {
	double deltaTime = event.time - m_lastTime;
	m_lastTime = event.time;

	m_timePassed += deltaTime;
	m_frameCount++;

	if (m_timePassed < 1.0f)
		return;

	float fps = m_frameCount / m_timePassed;

	m_timePassed = 0.0f;
	m_frameCount = 0;

	for (const Entity& entity : m_entities) {
		component::Text* text = m_world->getComponentManager<component::Text>().getComponent(entity);

		if (!text)
			continue;

		text->text = "FPS: " + std::to_string(static_cast<int>(fps));
		text->aligned = false;
	}
}


void	FpsCounter::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe(this, &FpsCounter::onRender);
}
