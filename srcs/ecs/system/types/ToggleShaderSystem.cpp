#include "ToggleShaderSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

ToggleShaderSystem::ToggleShaderSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Input>();
}

void	ToggleShaderSystem::onSimulate(const SimulateEvent& event) {
	auto& textureManager = m_world->getComponentManager<component::Texture>();
	for (size_t i = 0; i < textureManager.getComponentCount(); ++i) {
		component::Texture* texture = m_world->getComponentManager<component::Texture>().getComponentAtIndex(i);

		if (!texture)
			continue;

		if (texture->nextBlendOffset == 0.0f)
			continue;
		
		texture->blendFactor += texture->nextBlendOffset * event.deltaTime;

		if (texture->blendFactor < 0.0f) {
			texture->blendFactor = 0.0f;
			texture->nextBlendOffset = 0.0f;
		} else if (texture->blendFactor > 1.0f) {
			texture->blendFactor = 1.0f;
			texture->nextBlendOffset = 0.0f;
		}
	}
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

	auto& textureManager = m_world->getComponentManager<component::Texture>();
	for (size_t i = 0; i < textureManager.getComponentCount(); ++i) {
		component::Texture* texture = textureManager.getComponentAtIndex(i);

		if (!texture)
			continue;

		texture->nextBlendOffset = (texture->blendFactor == 0.0f) ? 1.0f : -1.0f;
	}
}

void	ToggleShaderSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<InputEvent>(this, &ToggleShaderSystem::onInput);
	dispatcher.subscribe<SimulateEvent>(this, &ToggleShaderSystem::onSimulate);
}
