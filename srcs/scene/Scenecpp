#include "Scene.hpp"

using namespace scene;

Scene::Scene() : camera{}, renderables{} {
}

Camera&	Scene::getCamera() {
	return camera;
}

const std::vector<Renderable>&	Scene::getRenderables() const {
	return renderables;
}

std::vector<Renderable>&	Scene::getRenderables() {
	return renderables;
}

const Renderable&	Scene::getRenderable(size_t index) const {
	return renderables[index];
}

Renderable&	Scene::getRenderable(size_t index) {
	return renderables[index];
}

void	Scene::addRenderable(const Renderable& renderable) {
	renderables.push_back(renderable);
}

void	Scene::removeRenderable(size_t index) {
	if (index < renderables.size()) {
		renderables.erase(renderables.begin() + index);
	}
}

Scene::~Scene() {
}
