#include "Components.hpp"

using namespace ecs::component;

ftm::vec3	Transform::forward() const {
	return rotation * scene::worldinfo::forward;
}

ftm::vec3	Transform::right() const {
	return rotation * scene::worldinfo::right;
}

ftm::vec3	Transform::left() const {
	return rotation * scene::worldinfo::left;
}

ftm::vec3	Transform::up() const {
	return rotation * scene::worldinfo::up;
}

ftm::vec3	Transform::down() const {
	return rotation * scene::worldinfo::down;
}

ftm::mat4	Transform::toModelMatrix() const {
	ftm::mat4 translation = ftm::translate(ftm::mat4(1.0f), position);
	ftm::mat4 rotationMat = ftm::toMat4(rotation);
	ftm::mat4 scaleMat = ftm::scale(ftm::mat4(1.0f), scale);

	return translation * rotationMat * scaleMat;
}
