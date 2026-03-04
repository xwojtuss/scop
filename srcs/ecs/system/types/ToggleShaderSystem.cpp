#include "ToggleShaderSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

ToggleShaderSystem::ToggleShaderSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Input>();
}

void	ToggleShaderSystem::onInput(const InputEvent& event) {
	(void)event;

	bool shouldToggle = false;
	for (const Entity& entity : m_entities) {
		component::Input* input = m_world->getComponentManager<component::Input>().getComponent(entity);

		if (!input)
			continue;

		if (render::input::hasEvent(input->command.startedEvents, render::input::InputEvent::ToggleShader)) {
			shouldToggle = true;
			break;
		}
	}

	if (!shouldToggle)
		return;

	auto& meshManager = m_world->getComponentManager<component::Mesh>();
	for (size_t i = 0; i < meshManager.getComponentCount(); ++i) {
		component::Mesh* mesh = meshManager.getComponentAtIndex(i);
		
		mesh->pipelineType = (mesh->pipelineType == assets::PipelineType::Textured) ? assets::PipelineType::VertexColor : assets::PipelineType::Textured;
	}
}

void	ToggleShaderSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<InputEvent>(this, &ToggleShaderSystem::onInput);
}
