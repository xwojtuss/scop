#pragma once

#include "../../render/input/InputTypes.hpp"

namespace render {
class IRenderer;
}

namespace ecs {

struct DispatchEvent {
protected:
	std::string	m_name;

	DispatchEvent(const std::string& name) : m_name(name) {}

public:
	virtual ~DispatchEvent() = default;

	const std::string&	getName() const { return m_name; }
};

struct RenderEvent : public DispatchEvent {
	float	aspectRatio;
	double	time;

	RenderEvent(float aspectRatio, double time) : DispatchEvent("RenderEvent"), aspectRatio(aspectRatio), time(time) {}
};

struct TextDrawEvent : public DispatchEvent {
	render::IRenderer*	renderer;

	TextDrawEvent(render::IRenderer* renderer) : DispatchEvent("TextDrawEvent"), renderer(renderer) {}
};

struct RendererDrawEvent : public DispatchEvent {
	render::IRenderer*	renderer;

	RendererDrawEvent(render::IRenderer* renderer) : DispatchEvent("RendererDrawEvent"), renderer(renderer) {}
};

struct RendererFrameEvent : public DispatchEvent {
	render::IRenderer*	renderer;

	RendererFrameEvent(render::IRenderer* renderer) : DispatchEvent("RendererFrameEvent"), renderer(renderer) {}
};

struct InputEvent : public DispatchEvent {
	float						deltaTime;
	ecs::Entity					source;
	render::input::InputCommand	command;

	InputEvent() : DispatchEvent("InputEvent"), deltaTime(0), source(-1) {}
};

struct WorldReadyEvent : public DispatchEvent {
	WorldReadyEvent() : DispatchEvent("WorldReadyEvent") {}
};

struct SimulateEvent : public DispatchEvent {
	float	deltaTime;
	float	time;

	SimulateEvent(float deltaTime, float time) : DispatchEvent("SimulateEvent"), deltaTime(deltaTime), time(time) {}
};

struct PlayerMoveEvent : public DispatchEvent {
	glm::vec3	previousPosition;
	glm::vec3	currentPosition;

	PlayerMoveEvent(glm::vec3 previousPosition, glm::vec3 currentPosition) : DispatchEvent("PlayerMoveEvent"), previousPosition(previousPosition), currentPosition(currentPosition) {}
};
}
