#pragma once

#include "../../render/input/InputTypes.hpp"

namespace render {
class IRenderer;
}

namespace ecs {
struct RenderEvent {
	float				aspectRatio;
};

struct RendererDrawEvent {
	render::IRenderer*	renderer;
};

struct RendererFrameEvent {
	render::IRenderer*	renderer;
};

struct InputEvent {
	render::input::InputCommand	command;
};

struct SimulateEvent {
	float	deltaTime;
};
}
