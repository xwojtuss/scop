#pragma once

#include <string>
#define ftm_ENABLE_EXPERIMENTAL
#include "ftm/ftm.hpp"

#include "Component.hpp"
#include "../../assets/Resources.hpp"
#include "../../scene/WorldInfo.hpp"
#include "../../render/input/InputTypes.hpp"

namespace ecs::component {
struct Transform : public Component<Transform> {
	ftm::vec3	position = ftm::vec3(0.0f, 0.0f, 0.0f);
	ftm::quat	rotation;
	ftm::vec3	scale = ftm::vec3(1.0f, 1.0f, 1.0f);
	bool		canRotate = true;

	ftm::vec3	forward() const;
	ftm::vec3	right() const;
	ftm::vec3	left() const;
	ftm::vec3	up() const;
	ftm::vec3	down() const;
	ftm::mat4	toModelMatrix() const;
};

struct Transform2D : public Component<Transform2D> {
	ftm::vec2	position;
	ftm::vec2	scale;
};

struct Velocity : public Component<Velocity> {
	ftm::vec3	velocity = ftm::vec3(0.0f);
	ftm::vec3	desiredVelocity = ftm::vec3(0.0f);
	float		maxSpeed;
	float		acceleration;
	float		decelleration;
	bool		canMove = true;
};

struct Camera : public Component<Camera> {
	ftm::mat4	view;
	ftm::mat4	projection;
	float		fov;
};

struct Mesh : public Component<Mesh> {
	assets::MeshHandle		mesh;
	assets::PipelineType	pipelineType;
};

struct Texture : public Component<Texture> {
	assets::TextureHandle	texture;

	// [0, 1] where 0 is the original texture and 1 is the color
	float					blendFactor = 0.0f;
	float					nextBlendOffset = 0.0f;
};

enum HAlignment {
	Left,
	Center,
	Right
};

enum VAlignment {
	Top = HAlignment::Left,
	Middle = HAlignment::Center,
	Bottom = HAlignment::Right
};

struct Text : public Component<Text>, public Mesh {
	std::string				text;
	HAlignment				horizontalAlignment = HAlignment::Left;
	VAlignment				verticalAlignment = VAlignment::Top;
	bool					aligned = false;

	Text() = default;
	Text(assets::MeshHandle textMeshHandle) {
		pipelineType = assets::PipelineType::Text;
		mesh = textMeshHandle;
		this->text = "";
	}
};

struct Input : public Component<Input> {
	render::input::InputCommand	command;
	float						mouseSensitivity;
};

struct Color : public Component<Color> {
	ftm::vec4	color;
};

enum AnimationType {
	Spin,
	Bounce,
	Jitter,
	Random,
	Circle,
	Pulse
};

struct Animation : public Component<Animation> {
	float			speed = 1.0f;
	float			intensity = 1.0f;
	AnimationType	type;
};
}