#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

#include "../IGui.hpp"

namespace render::vulkan {
class VulkanContext;
class VulkanSwapchain;
}

namespace platform::window {
class IWindow;
}

namespace render::gui::vulkan {

class ImGuiGui : public IGui {
private:
	render::vulkan::VulkanContext&		m_context;
	render::vulkan::VulkanSwapchain&	m_swapchain;
	platform::window::IWindow&			m_window;
	ImGuiContext*						m_imguiContext;
	VkDescriptorPool					m_descriptorPool;
	int									m_windowDepth;
	bool								m_isInitialized;

	void	createDescriptorPool();
	void	init();

public:
	ImGuiGui(render::vulkan::VulkanContext& context, render::vulkan::VulkanSwapchain& swapchain, platform::window::IWindow& window);
	~ImGuiGui();


	void	beginFrame() override;
	void	endFrame() override;
	bool	beginWindow(const std::string& name, const glm::vec2& size, bool* open = nullptr) override;
	void	endWindow() override;
	void	text(const std::string& value) override;
	bool	button(const std::string& label) override;
	void	render(VkCommandBuffer commandBuffer) override;
	bool	wantsMouseCapture() const override;
	bool	wantsKeyboardCapture() const override;
};
}
