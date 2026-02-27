#pragma once

#include <memory>

#include "../platform/window/IWindow.hpp"
#include "../render/IRenderer.hpp"
#include "../assets/IModelLoader.hpp"
#include "../assets/ITextureLoader.hpp"
#include "../platform/window/glfw/GLFWWindow.hpp"
#include "../render/vulkan/VulkanRenderer.hpp"
#include "../assets/TinyObjLoader.hpp"
#include "../assets/StbTextureLoader.hpp"
#include "../ecs/entity/EntityHandle.hpp"
#include "../ecs/system/types/CameraSystem.hpp"
#include "../ecs/system/types/MovementSystem.hpp"
#include "../ecs/system/types/PlayerInputSystem.hpp"
#include "../ecs/system/types/RenderSystem.hpp"
#include "../ecs/system/types/WindowControlSystem.hpp"
#include "../ecs/component/Components.hpp"
#include "../ecs/World.hpp"

namespace app {
class Application {
private:
	std::unique_ptr<platform::window::IWindow>		m_window;
	std::unique_ptr<render::IRenderer>				m_renderer;
	std::unique_ptr<ecs::World>						m_world;
	std::unique_ptr<assets::IModelLoader>			m_modelLoader;
	std::unique_ptr<assets::ITextureLoader>			m_textureLoader;

	void	init();

	/**
	 * Runs once per render frame
	 */
	void	update();

	/**
	 * Runs once per app::simulationFPS
	 */
	void	simulate();
	void	render();

public:
	Application();

	void	run();
};
}