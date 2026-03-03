#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Component.hpp"
#include "../../assets/Resources.hpp"
#include "../../scene/WorldInfo.hpp"
#include "../../render/input/InputTypes.hpp"

namespace ecs::component {
struct Transform : public Component<Transform> {
	glm::vec3	position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat	rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	bool		canRotate = true;

	glm::vec3	forward() const;
	glm::vec3	right() const;
	glm::vec3	left() const;
	glm::vec3	up() const;
	glm::vec3	down() const;
	glm::mat4	toModelMatrix() const;
};

struct Transform2D : public Component<Transform2D> {
	glm::vec2	position;
	glm::vec2	scale;
};

struct Velocity : public Component<Velocity> {
	glm::vec3	velocity;
	glm::vec3	desiredVelocity;
	float		maxSpeed;
	float		acceleration;
	float		decelleration;
	bool		canMove = true;
};

struct Camera : public Component<Camera> {
	glm::mat4	view;
	glm::mat4	projection;
	float		fov;
};

struct Mesh : public Component<Mesh> {
	assets::MeshHandle		mesh;
	assets::PipelineType	pipelineType;
};

struct Texture : public Component<Texture> {
	assets::TextureHandle	texture;
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
	glm::vec4	color;
};
}