#pragma once

#include <vector>

#include "ObjectProperties.hpp"
#include "Camera.hpp"

namespace scene {
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
