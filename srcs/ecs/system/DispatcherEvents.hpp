#pragma once

#include "../../render/input/InputTypes.hpp"

namespace render {
class IRenderer;
}

namespace ecs {
struct RenderEvent {
	float	aspectRatio;
	double	time;
};

struct TextDrawEvent {
	render::IRenderer*	renderer;
};

struct RendererDrawEvent {
	render::IRenderer*	renderer;
};

struct RendererFrameEvent {
	render::IRenderer*	renderer;
};

struct InputEvent {
	float						deltaTime;
	ecs::Entity					source;
	render::input::InputCommand	command;
};

struct WorldReadyEvent {
};

struct SimulateEvent {
	float	deltaTime;
	float	time;
};
}
