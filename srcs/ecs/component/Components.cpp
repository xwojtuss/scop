#include "Components.hpp"

using namespace ecs::component;

glm::vec3	Transform::forward() const {
	return rotation * scene::worldinfo::forward;
}

glm::vec3	Transform::right() const {
	return rotation * scene::worldinfo::right;
}

glm::vec3	Transform::left() const {
	return rotation * scene::worldinfo::left;
}

glm::vec3	Transform::up() const {
	return rotation * scene::worldinfo::up;
}

glm::vec3	Transform::down() const {
	return rotation * scene::worldinfo::down;
}

glm::mat4	Transform::toModelMatrix() const {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMat = glm::toMat4(rotation);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

	return translation * rotationMat * scaleMat;
}
