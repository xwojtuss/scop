#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Component.hpp"
#include "../../assets/Resources.hpp"
#include "../../scene/WorldInfo.hpp"

namespace ecs::component {
struct Transform : public Component<Transform> {
	glm::vec3	position;
	glm::quat	rotation;
	glm::vec3	scale;

	glm::vec3	forward() const;
	glm::vec3	right() const;
	glm::vec3	left() const;
	glm::vec3	up() const;
	glm::vec3	down() const;
	glm::mat4	toModelMatrix() const;
};

struct Velocity : public Component<Velocity> {
	glm::vec3	velocity;
	glm::vec3	desiredVelocity;
	float		maxSpeed;
	float		acceleration;
};

struct Camera : public Component<Camera> {
	glm::mat4	view;
	glm::mat4	projection;
	float		fov;
};

struct Mesh : public Component<Mesh> {
	assets::MeshHandle		mesh;
	assets::TextureHandle	texture;
};
}