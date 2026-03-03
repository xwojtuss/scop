#include "Application.hpp"

using namespace app;

Application::Application() {
	m_window = std::make_unique<platform::window::glfw::GLFWWindow>();
	m_renderer = std::make_unique<render::vulkan::VulkanRenderer>(*m_window);
	m_world = std::make_unique<ecs::World>();
	m_modelLoader = std::make_unique<assets::BasicObjLoader>();
	// m_modelLoader = std::make_unique<assets::TinyObjLoader>();
	m_textureLoader = std::make_unique<assets::StbTextureLoader>();

	m_window->getInputManager().getKeyInputProcessor().resetBindings();

	init();
}

void	Application::init() {
	m_world->createSystem<ecs::CameraSystem>();
	m_world->createSystem<ecs::MovementSystem>();
	m_world->createSystem<ecs::RenderSystem>();
	m_world->createSystem<ecs::TextRenderSystem>();
	m_world->createSystem<ecs::WindowControlSystem>(*m_window);
	m_world->createSystem<ecs::PlayerInputSystem>(m_window->getInputManager());
	m_world->createSystem<ecs::FpsCounter>();

	ecs::EntityHandle camera = m_world->createEntity();
	ecs::component::Transform transform{};
	ecs::component::Velocity velocity{};
	ecs::component::Camera cameraComponent{};
	ecs::component::Input inputComponent{};

	transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	velocity.acceleration = 4.5f;
	velocity.decelleration = 10.0f;
	velocity.maxSpeed = 10.0f;
	velocity.velocity = glm::vec3(0.0f);
	velocity.desiredVelocity = glm::vec3(0.0f);
	cameraComponent.fov = 90.0f;
	inputComponent.mouseSensitivity = 0.002f;
	camera.addComponent(transform);
	camera.addComponent(velocity);
	camera.addComponent(cameraComponent);
	camera.addComponent(inputComponent);

	camera.registerToSystem<ecs::MovementSystem>();
	camera.registerToSystem<ecs::PlayerInputSystem>();
	camera.registerToSystem<ecs::CameraSystem>();
	camera.registerToSystem<ecs::WindowControlSystem>();

	ecs::EntityHandle renderableEntity = m_world->createEntity();
	ecs::component::Transform renderableTransform{};
	ecs::component::Mesh meshComponent{};

	renderableTransform.position = scene::worldinfo::forward * 2.0f;
	renderableTransform.rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	renderableTransform.rotation = glm::rotate(renderableTransform.rotation, glm::radians(180.0f), scene::worldinfo::up);
	renderableTransform.rotation = glm::rotate(renderableTransform.rotation, glm::radians(90.0f), scene::worldinfo::left);
	renderableTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	meshComponent.mesh = m_renderer->createMesh(m_modelLoader->toMeshData("models/room.obj"));
	meshComponent.texture = m_renderer->createTexture(m_textureLoader->toTextureData("textures/room.png"));
	meshComponent.pipelineType = assets::PipelineType::Textured;

	renderableEntity.addComponent(renderableTransform);
	renderableEntity.addComponent(meshComponent);
	renderableEntity.registerToSystem<ecs::RenderSystem>();

	ecs::EntityHandle fpsCounter = m_world->createEntity();
	ecs::component::Transform2D textTransform2{};
	ecs::component::Text textComponent2{};
	textTransform2.position = glm::vec2(-1.0f, -1.0f);
	textTransform2.scale = glm::vec2(0.02f, 0.06f);
	textComponent2.text = "";
	textComponent2.horizontalAlignment = ecs::component::HAlignment::Left;
	textComponent2.verticalAlignment = ecs::component::VAlignment::Top;
	assets::TextureData fontTextureData2 = m_textureLoader->toTextureData("textures/monogram-bitmap.png");
	fontTextureData2.pixelPerfect = true;
	textComponent2.font = m_renderer->createTexture(fontTextureData2);
	fpsCounter.addComponent(textTransform2);
	fpsCounter.addComponent(textComponent2);
	fpsCounter.registerToSystem<ecs::TextRenderSystem>();
	fpsCounter.registerToSystem<ecs::FpsCounter>();

	ecs::EntityHandle floor = m_world->createEntity();
	ecs::component::Transform floorTransform{};
	ecs::component::Mesh floorMesh{};
	float floorSize = 100.0f;
	floorTransform.position = glm::vec3(-floorSize / 2.0f, -5.0f, floorSize / 2.0f);
	floorTransform.scale = glm::vec3(floorSize, floorSize, 1.0f);
	floorTransform.rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	floorTransform.rotation = glm::rotate(floorTransform.rotation, glm::radians(90.0f), scene::worldinfo::left);
	assets::TextureData floorTextureData = m_textureLoader->toTextureData("textures/flower.jpg");
	assets::MeshData floorMeshData;
	floorMeshData.vertices = {
		{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
		{{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
	};
	floorMeshData.indices = {
		0, 1, 2,
		2, 3, 0
	};
	floorMesh.mesh = m_renderer->createMesh(floorMeshData);
	floorMesh.texture = m_renderer->createTexture(floorTextureData);
	floorMesh.pipelineType = assets::PipelineType::Textured;
	floor.addComponent(floorTransform);
	floor.addComponent(floorMesh);
	floor.registerToSystem<ecs::RenderSystem>();
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
	m_world->getSystemManager().onRender(m_window->getAspectRatio(), m_window->getTime());
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
