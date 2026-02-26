#pragma once

#include <glm/glm.hpp>

#include "../platform/window/IWindow.hpp"
#include "ObjectProperties.hpp"
#include "WorldInfo.hpp"

namespace scene {
class Camera {
private:
	Transform	m_transform;
	glm::mat4	m_view;
	glm::mat4	m_projection;
	glm::vec3	m_velocity;
	glm::vec3	m_inputDir;
	float		m_maxSpeed;
	float		m_accelScalar;
	bool		m_isMoving;

	// in degrees
	float		fov;

public:

	Camera();
	~Camera();

	void				updateView();
	void				updateProjection(float aspectRatio);
	void				startMoving(float accelerationForward, float accelerationRight);
	void				move(float deltaTime);
	void				stopMoving();
	Transform&			getTransform();
	const Transform&	getTransform() const;
	const glm::mat4&	getView() const;
	const glm::mat4&	getProjection() const;
	float				getFov() const;
};
}
