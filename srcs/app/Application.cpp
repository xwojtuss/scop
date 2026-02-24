#include "Application.hpp"

using namespace app;

Application::Application(const scene::Scene& scene) : m_scene(std::make_unique<scene::Scene>(scene)) {
	m_window = std::make_unique<platform::window::glfw::GLFWWindow>();
	m_renderer = std::make_unique<render::vulkan::VulkanRenderer>(*m_window);
	m_modelLoader = std::make_unique<assets::TinyObjLoader>();
	m_textureLoader = std::make_unique<assets::StbTextureLoader>();
}

void	Application::run() {
	scene::Renderable renderable;

	renderable.mesh = m_renderer->createMesh(m_modelLoader->toMeshData("models/room.obj"));
	renderable.texture = m_renderer->createTexture(m_textureLoader->toTextureData("textures/room.png"));
	renderable.transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	renderable.transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	renderable.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_scene->addRenderable(renderable);

	scene::Renderable renderable2(renderable);

	renderable2.transform.position = glm::vec3(0.0f, 0.0f, -2.0f);

	m_scene->addRenderable(renderable2);

	while (!m_window->shouldClose()) {
		m_window->pollEvents();
		update();
		render();
	}
}

void	Application::update() {
	double temp = 0.5f * sin(m_window->getTime());
	double temp2 = 0.5f * cos(m_window->getTime());

	m_scene->getRenderable(0).transform.position.x = -temp;
	m_scene->getRenderable(0).transform.position.y = temp2;
	
	m_scene->getRenderable(1).transform.scale = glm::vec3(1.0f + temp, 1.0f - temp, 1.0f + temp);
	m_scene->getRenderable(1).transform.rotation = glm::rotate(m_scene->getRenderable(1).transform.rotation, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void	Application::render() {
	m_renderer->beginFrame();
	m_renderer->render(*m_scene);
	m_renderer->endFrame();
}
