#include "Camera.hpp"

using namespace scene;

Camera::Camera() : m_transform{}, m_moveSpeed(2.5f), fov(45.0f) {
	updateView();
	updateProjection(platform::window::aspectRatio);
}

void	Camera::updateProjection(float aspectRatio) {
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 10.0f);
}

void	Camera::updateView() {
	m_view = glm::lookAt(m_transform.position, m_transform.position + m_transform.forward(), m_transform.up());
}

Transform&	Camera::getTransform() {
	return m_transform;
}

const Transform&	Camera::getTransform() const {
	return m_transform;
}

const glm::mat4&	Camera::getView() const {
	return m_view;
}

const glm::mat4&	Camera::getProjection() const {
	return m_projection;
}

float	Camera::getMoveSpeed() const {
	return m_moveSpeed;
}

float	Camera::getFov() const {
	return fov;
}

Camera::~Camera() {
}
