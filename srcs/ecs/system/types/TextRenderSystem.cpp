#include "TextRenderSystem.hpp"
#include "../../World.hpp"

using namespace ecs;

TextRenderSystem::TextRenderSystem() : ASystem(Dependencies()) {
	m_dependencies.addDependency<component::Transform2D>();
	m_dependencies.addDependency<component::Text>();
}

void	TextRenderSystem::alignText(component::Text& text, component::Transform2D& transform) {
	transform.position -= glm::vec2(text.horizontalAlignment, text.verticalAlignment) * glm::vec2(text.text.length(), 1.0f) * 0.5f * transform.scale;
	text.aligned = true;
}

void	TextRenderSystem::onTextDraw(const TextDrawEvent& event) {
	size_t offset = 0;

	for (const Entity& entity : m_entities) {
		component::Transform2D* transform = m_world->getComponentManager<component::Transform2D>().getComponent(entity);
		component::Text* text = m_world->getComponentManager<component::Text>().getComponent(entity);

		if (!transform || !text || text->text.empty())
			continue;

		const component::Color* color = m_world->getComponentManager<component::Color>().getComponent(entity);

		if (!text->aligned)
			alignText(*text, *transform);

		event.renderer->drawText(text->text, text->font, *transform, offset, color);
		offset += text->text.length();
	}
}

void	TextRenderSystem::bindEvents(Dispatcher& dispatcher) {
	dispatcher.subscribe<TextDrawEvent>(this, &TextRenderSystem::onTextDraw);
}
