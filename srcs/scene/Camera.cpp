#include "Camera.hpp"

using namespace scene;

Camera::Camera() : m_transform(), m_view(1.0f), m_projection(1.0f), m_velocity(0.0f), m_inputDir(0.0f), m_maxSpeed(5.0f), m_accelScalar(2.0f), m_isMoving(false), fov(60.0f) {
	updateView();
	updateProjection(platform::window::aspectRatio);
}

void	Camera::updateProjection(float aspectRatio) {
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 10.0f);
}

void	Camera::updateView() {
	m_view = glm::lookAt(m_transform.position, m_transform.position + m_transform.forward(), m_transform.up());
}

void	Camera::startMoving(float accelerationForward, float accelerationRight) {
	m_inputDir = glm::vec3(accelerationForward, accelerationRight, 0.0f);
	m_isMoving = true;
}

void Camera::move(float dt)
{
	glm::vec3 desiredVelocity = m_inputDir * m_maxSpeed;
	glm::vec3 delta = desiredVelocity - m_velocity;

	m_velocity += delta * ((glm::length2(m_inputDir) > 0.0f) ? m_accelScalar * dt : worldinfo::drag * dt);

	if (glm::length(m_velocity) > m_maxSpeed)
		m_velocity = glm::normalize(m_velocity) * m_maxSpeed;

	m_transform.move(
		m_velocity.x * dt,
		m_velocity.y * dt,
		0.0f
	);
}

void	Camera::stopMoving() {
	// m_velocity = glm::vec3(0.0f);
	m_inputDir = glm::vec3(0.0f);

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

float	Camera::getFov() const {
	return fov;
}

Camera::~Camera() {
}
