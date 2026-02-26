#include "ObjectProperties.hpp"

// This will one day hopefully be turned into components

namespace scene {
Transform::Transform() : position(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) {}

Transform::operator glm::mat4() const {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMat = glm::toMat4(rotation);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

	return translation * rotationMat * scaleMat;
}

glm::vec3	Transform::forward() const {
	return rotation * worldinfo::forward;
}

glm::vec3	Transform::right() const {
	return rotation * worldinfo::right;
}

glm::vec3	Transform::left() const {
	return rotation * worldinfo::left;
}

glm::vec3	Transform::up() const {
	return rotation * worldinfo::up;
}

glm::vec3	Transform::down() const {
	return rotation * worldinfo::down;
}

void	Transform::moveLockY(float deltaForward, float deltaRight, float deltaUp) {
	glm::vec3 forward = glm::normalize(glm::vec3(rotation * glm::vec3(0,0,-1)));

	forward.y = 0;
	forward = glm::normalize(forward);

	glm::vec3 right = glm::normalize(glm::vec3(rotation * glm::vec3(1,0,0)));
	right.y = 0;

	position += forward * deltaForward + right * deltaRight + glm::vec3(0,1,0) * deltaUp;
}

void	Transform::move(float deltaForward, float deltaRight, float deltaUp) {
	glm::vec3 forward = rotation * glm::vec3(0,0,-1);
	glm::vec3 right = rotation * glm::vec3(1,0,0);

	position += forward * deltaForward + right * deltaRight + glm::vec3(0,1,0) * deltaUp;
}

void	Transform::rotate(float angleX, float angleY) {
	float pitch = std::asin(glm::clamp(forward().y, -1.0f, 1.0f));
	float clampedDelta = glm::clamp(pitch + angleX, -maxPitch, maxPitch) - pitch;
	
	if (clampedDelta > maxPitch) clampedDelta = maxPitch;
	else if (clampedDelta < -maxPitch) clampedDelta = -maxPitch;
	
	glm::quat rotX = glm::angleAxis(clampedDelta, right());
	glm::quat rotY = glm::angleAxis(angleY, worldinfo::up);
	rotation = glm::normalize(rotY * rotX * rotation);
}

void	Transform::scaleBy(const glm::vec3& factor) {
	scale *= factor;
}

void	Transform::scaleBy(float factor) {
	scale *= factor;
}
};
