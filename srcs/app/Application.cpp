#include "Application.hpp"

using namespace app;

Application::Application(const scene::Scene& scene) : m_scene(std::make_unique<scene::Scene>(scene)) {
	m_window = std::make_unique<platform::window::glfw::GLFWWindow>();
	m_renderer = std::make_unique<render::vulkan::VulkanRenderer>(*m_window);
	m_modelLoader = std::make_unique<assets::TinyObjLoader>();
	m_textureLoader = std::make_unique<assets::StbTextureLoader>();

	m_window->getInputManager().getKeyInputProcessor().resetBindings();
}

void	Application::run() {
	scene::Renderable renderable;

	renderable.mesh = m_renderer->createMesh(m_modelLoader->toMeshData("models/room.obj"));
	renderable.texture = m_renderer->createTexture(m_textureLoader->toTextureData("textures/room.png"));
	renderable.transform.position = glm::vec3(0.0f, 0.0f, 2.0f);
	renderable.transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	renderable.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_scene->addRenderable(renderable);

	scene::Renderable renderable2(renderable);

	renderable2.transform.position = glm::vec3(0.0f, 0.0f, -2.0f);

	m_scene->addRenderable(renderable2);

	scene::Renderable renderable3(renderable);

	renderable3.transform.position = glm::vec3(2.0f, 0.0f, 0.0f);

	m_scene->addRenderable(renderable3);

	scene::Renderable renderable4(renderable);

	renderable4.transform.position = glm::vec3(-2.0f, 0.0f, 0.0f);

	m_scene->addRenderable(renderable4);

	scene::Renderable renderable5(renderable);

	renderable5.transform.position = glm::vec3(0.0f, 2.0f, 0.0f);

	m_scene->addRenderable(renderable5);

	scene::Renderable renderable6(renderable);

	renderable6.transform.position = glm::vec3(0.0f, -2.0f, 0.0f);

	m_scene->addRenderable(renderable6);

	while (!m_window->shouldClose()) {
		m_window->pollEvents();
		simulate();
		update();
		render();
	}
}

void	Application::update() {
	// auto time = m_window->getTime();
	// double temp = 0.5f * sin(time);
	// double temp2 = 0.5f * cos(time);

	// m_scene->getRenderable(0).transform.position.x = -temp;
	// m_scene->getRenderable(0).transform.position.y = temp2;
	
	// m_scene->getRenderable(1).transform.scale = glm::vec3(1.0f + temp, 1.0f - temp, 1.0f + temp);
	// m_scene->getRenderable(1).transform.rotation = glm::rotate(m_scene->getRenderable(1).transform.rotation, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void	Application::simulate() {
	double time = m_window->getTime();
	static double lastSimulateTime = 0.0;
	auto dt = time - lastSimulateTime;
	
	if (m_window->wasResized() || time - lastSimulateTime < simulationFrameRate) {
		return;
	}
	lastSimulateTime = time;

	render::input::InputCommand	command = m_window->getInputManager().buildCommand();

	if (render::input::hasAnyEvent(command.activeEvents, render::input::InputEvent::AnyMove))
		m_scene->getCamera().startMoving(command.moveForward, command.moveRight, command.moveUp);
	else
		m_scene->getCamera().stopMoving();

	m_scene->getCamera().move(dt);
	m_scene->getCamera().getTransform().rotate(command.lookUp * dt, command.lookRight * dt);
	m_scene->getCamera().updateView();
}

void	Application::render() {
	m_renderer->beginFrame();
	m_renderer->render(*m_scene);
	m_renderer->endFrame();
}
