#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

#include "WorldInfo.hpp"
#include "../assets/Resources.hpp"

// This will one day hopefully be turned into components

namespace scene {
constexpr float		maxPitch = glm::radians(80.0f);
struct Transform {
	glm::vec3	position;
	glm::quat	rotation;
	glm::vec3	scale;

	Transform();

	glm::vec3	forward() const;
	glm::vec3	right() const;
	glm::vec3	left() const;
	glm::vec3	up() const;
	glm::vec3	down() const;
	void	move(float deltaForward, float deltaRight, float deltaUp);
	void	moveLockY(float deltaForward, float deltaRight, float deltaUp);
	void	rotate(float angleX, float angleY);
	void	scaleBy(const glm::vec3& factor);
	void	scaleBy(float factor);

	operator glm::mat4() const;
};

struct Renderable {
	assets::MeshHandle		mesh;
	assets::TextureHandle	texture;
	// assets::PipelineHandle	pipeline;
	Transform				transform;
};
}
