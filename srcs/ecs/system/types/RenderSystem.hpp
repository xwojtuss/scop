#pragma once

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../render/IRenderer.hpp"

namespace ecs {
class RenderSystem : public ASystem {
public:
	RenderSystem();

	void			onRendererDraw(const RendererDrawEvent& event);
	virtual void	bindEvents(Dispatcher& dispatcher) override;
};
}
