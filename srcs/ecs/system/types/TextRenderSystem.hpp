#pragma once

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../render/IRenderer.hpp"

namespace ecs {
class TextRenderSystem : public ASystem {
private:
	static void	alignText(component::Text& text, component::Transform2D& transform);

public:
	TextRenderSystem();

	void			onTextDraw(const TextDrawEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
