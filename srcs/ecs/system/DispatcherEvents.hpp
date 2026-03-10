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
	render::input::InputCommand	command;
	float						mouseSensitivity;
	float						deltaTime;
};

struct SimulateEvent {
	float	deltaTime;
	float	time;
};
}
