#pragma once

#include <string>

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"
#include "../../../render/IRenderer.hpp"

namespace ecs {
class World;

class CameraSystem : public ASystem {
public:
	CameraSystem();
	~CameraSystem() = default;

	void					onRender(const RenderEvent& event);
	void					onRendererFrame(const RendererFrameEvent& event);
	virtual void			bindEvents(Dispatcher& dispatcher) override;
};
}
