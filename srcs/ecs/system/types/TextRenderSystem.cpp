#include "TextRenderSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

TextRenderSystem::TextRenderSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform2D>();
	m_dependencies.addDependency<component::Text>();
}

void	TextRenderSystem::onTextDraw(const TextDrawEvent& event) {
	for (const Entity& entity : m_entities) {
		const component::Transform2D* transform = m_world->getComponentManager<component::Transform2D>().getComponent(entity);
		const component::Text* text = m_world->getComponentManager<component::Text>().getComponent(entity);

		if (!transform || !text)
			continue;

		const component::Color* color = m_world->getComponentManager<component::Color>().getComponent(entity);

		event.renderer->drawText(text->text, text->font, *transform, color);
	}
}

void	TextRenderSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<TextDrawEvent>(this, &TextRenderSystem::onTextDraw);
}
