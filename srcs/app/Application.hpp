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

namespace app {
class Application {
private:
	std::unique_ptr<platform::window::IWindow>		m_window;
	std::unique_ptr<render::IRenderer>				m_renderer;
	std::unique_ptr<scene::Scene>					m_scene;
	std::unique_ptr<assets::IModelLoader>			m_modelLoader;
	std::unique_ptr<assets::ITextureLoader>			m_textureLoader;

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
	Application(const scene::Scene& scene);

	void	run();
};
}