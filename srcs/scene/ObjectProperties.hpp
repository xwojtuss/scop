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

	Transform() : position(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) {}

	operator glm::mat4() const {
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMat = glm::toMat4(rotation);
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

		return translation * rotationMat * scaleMat;
	}

	glm::vec3	forward() const {
		return rotation * worldinfo::forward;
	}

	glm::vec3	right() const {
		return rotation * worldinfo::right;
	}

	glm::vec3	left() const {
		return rotation * worldinfo::left;
	}

	glm::vec3	up() const {
		return rotation * worldinfo::up;
	}

	glm::vec3	down() const {
		return rotation * worldinfo::down;
	}

	void	move(const glm::vec3& delta) {
		position += delta;
	}

	void	rotate(float angleX, float angleY) {
		float pitch = std::asin(glm::clamp(forward().y, -1.0f, 1.0f));
		float clampedDelta = glm::clamp(pitch + angleX, -maxPitch, maxPitch) - pitch;
		
		if (clampedDelta > maxPitch) clampedDelta = maxPitch;
		else if (clampedDelta < -maxPitch) clampedDelta = -maxPitch;
		
		glm::quat rotX = glm::angleAxis(clampedDelta, right());
		glm::quat rotY = glm::angleAxis(angleY, worldinfo::up);
		rotation = glm::normalize(rotY * rotX * rotation);
	}

	void	scaleBy(const glm::vec3& factor) {
		scale *= factor;
	}

	void	scaleBy(float factor) {
		scale *= factor;
	}
};

struct Renderable {
	assets::MeshHandle		mesh;
	assets::TextureHandle	texture;
	// assets::PipelineHandle	pipeline;
	Transform				transform;
};
}
