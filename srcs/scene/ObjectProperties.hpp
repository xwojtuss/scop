#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../assets/Resources.hpp"

// This will one day hopefully be turned into components

namespace scene {
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
		return rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	glm::vec3	right() const {
		return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}

	glm::vec3	left() const {
		return rotation * glm::vec3(-1.0f, 0.0f, 0.0f);
	}

	glm::vec3	up() const {
		return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::vec3	down() const {
		return rotation * glm::vec3(0.0f, -1.0f, 0.0f);
	}

	void	move(const glm::vec3& delta) {
		position += delta;
	}

	void	rotate(float angle, const glm::vec3& axis) {
		rotation = glm::rotate(rotation, angle, axis);
	}

	void	rotate(const glm::quat& delta) {
		rotation = delta * rotation;
	}

	void	rotate(float angleX, float angleY, float angleZ) {
		rotation = glm::rotate(rotation, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void	rotate(float angleX, float angleY) {
		rotation = glm::rotate(rotation, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, angleX, right());
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
