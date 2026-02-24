#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../platform/window/IWindow.hpp"
#include "../assets/Resources.hpp"

namespace scene {
struct Transform {
	glm::vec3	position;
	glm::quat	rotation;
	glm::vec3	scale;

	operator glm::mat4() const {
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMat = glm::toMat4(rotation);
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

		return translation * rotationMat * scaleMat;
	}
};

struct Camera {
	glm::mat4	view;
	glm::mat4	projection;

	// in degrees
	float		fov = 45.0f;

	Camera() {
		view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		updateProjection(platform::window::aspectRatio);
	}

	void	updateProjection(float aspectRatio) {
		projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 10.0f);
	}
};

struct Renderable {
	assets::MeshHandle		mesh;
	assets::TextureHandle	texture;
	// assets::PipelineHandle	pipeline;
	Transform				transform;
};

class Scene {
private:
	Camera					camera;
	std::vector<Renderable>	renderables;

public:
	Scene();
	~Scene();

	Camera&							getCamera();
	const std::vector<Renderable>&	getRenderables() const;
	std::vector<Renderable>&		getRenderables();
	const Renderable&				getRenderable(size_t index) const;
	Renderable&						getRenderable(size_t index);
	void							addRenderable(const Renderable& renderable);
	void							removeRenderable(size_t index);

};
}
