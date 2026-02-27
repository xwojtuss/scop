#include "Application.hpp"

using namespace app;

Application::Application() {
	m_window = std::make_unique<platform::window::glfw::GLFWWindow>();
	m_renderer = std::make_unique<render::vulkan::VulkanRenderer>(*m_window);
	m_world = std::make_unique<ecs::World>();
	m_modelLoader = std::make_unique<assets::TinyObjLoader>();
	m_textureLoader = std::make_unique<assets::StbTextureLoader>();

	m_window->getInputManager().getKeyInputProcessor().resetBindings();

	init();
}

void	Application::init() {
	m_world->createSystem<ecs::CameraSystem>();
	m_world->createSystem<ecs::MovementSystem>();
	m_world->createSystem<ecs::RenderSystem>();
	m_world->createDispatchingSystem<ecs::PlayerInputSystem>(m_window->getInputManager());

	ecs::EntityHandle camera = m_world->createEntity();
	ecs::component::Transform transform{};
	ecs::component::Velocity velocity{};
	ecs::component::Camera cameraComponent{};
	ecs::component::Input inputComponent{};

	transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
	transform.rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	velocity.acceleration = 4.5f;
	velocity.decelleration = 10.0f;
	velocity.maxSpeed = 100.0f;
	velocity.velocity = glm::vec3(0.0f);
	velocity.desiredVelocity = glm::vec3(0.0f);
	cameraComponent.fov = 60.0f;
	inputComponent.mouseSensitivity = 1.0f;
	camera.addComponent(transform);
	camera.addComponent(velocity);
	camera.addComponent(cameraComponent);
	camera.addComponent(inputComponent);

	camera.registerToSystem<ecs::MovementSystem>();
	camera.registerToSystem<ecs::PlayerInputSystem>();
	camera.registerToSystem<ecs::CameraSystem>();

	ecs::EntityHandle renderableEntity = m_world->createEntity();
	ecs::component::Transform renderableTransform{};
	ecs::component::Mesh meshComponent{};

	renderableTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	renderableTransform.rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	renderableTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	meshComponent.mesh = m_renderer->createMesh(m_modelLoader->toMeshData("models/room.obj"));
	meshComponent.texture = m_renderer->createTexture(m_textureLoader->toTextureData("textures/room.png"));

	renderableEntity.addComponent(renderableTransform);
	renderableEntity.addComponent(meshComponent);
	renderableEntity.registerToSystem<ecs::RenderSystem>();
}

void	Application::run() {
	while (!m_window->shouldClose()) {
		m_window->pollEvents();
		simulate();
		update();
		render();
	}
}

void	Application::update() {
	m_world->getSystemManager().onRender(m_window->getAspectRatio());
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

	m_world->getSystemManager().onSimulate(static_cast<float>(dt));
}

void	Application::render() {
	m_renderer->beginFrame();
	m_renderer->render(m_world->getSystemManager());
	m_renderer->endFrame();
}
