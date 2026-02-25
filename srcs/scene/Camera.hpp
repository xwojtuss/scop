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
	float		m_moveSpeed;

	// in degrees
	float		fov;

public:

	Camera();
	~Camera();

	void				updateView();
	void				updateProjection(float aspectRatio);
	Transform&			getTransform();
	const Transform&	getTransform() const;
	const glm::mat4&	getView() const;
	const glm::mat4&	getProjection() const;
	float				getMoveSpeed() const;
	float				getFov() const;
};
}
