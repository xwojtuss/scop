#include "ImGuiGui.hpp"
#include "../../vulkan/VulkanContext.hpp"
#include "../../vulkan/VulkanSwapchain.hpp"
#include "../../../platform/window/IWindow.hpp"

#include <GLFW/glfw3.h>

using namespace render::gui::vulkan;

ImGuiGui::ImGuiGui(render::vulkan::VulkanContext& context, render::vulkan::VulkanSwapchain& swapchain, platform::window::IWindow& window)
	: m_context(context), m_swapchain(swapchain), m_window(window), m_imguiContext(nullptr), m_descriptorPool(VK_NULL_HANDLE), m_windowDepth(0), m_isInitialized(false) {
	m_imguiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(m_imguiContext);
	createDescriptorPool();
	init();
}

void	ImGuiGui::createDescriptorPool() {
	constexpr const std::size_t	poolSize = 1000;

	VkDescriptorPoolSize pool_sizes[] = {
		{ VK_DESCRIPTOR_TYPE_SAMPLER, poolSize },
		{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, poolSize },
		{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, poolSize },
		{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, poolSize },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, poolSize },
		{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, poolSize },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, poolSize },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, poolSize },
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, poolSize },
		{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, poolSize },
		{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, poolSize }
	};

	VkDescriptorPoolCreateInfo pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	pool_info.maxSets = poolSize;
	pool_info.poolSizeCount = sizeof(pool_sizes) / sizeof(pool_sizes[0]);
	pool_info.pPoolSizes = pool_sizes;

	if (vkCreateDescriptorPool(m_context.getLogicalDevice(), &pool_info, nullptr, &m_descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create ImGui descriptor pool!");
	}
}

void	ImGuiGui::init() {
	ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(m_window.getHandle()), true);

	ImGui_ImplVulkan_InitInfo init_info = {};
	init_info.ApiVersion = VK_API_VERSION_1_3;
	init_info.Instance = m_context.getInstance();
	init_info.PhysicalDevice = m_context.getPhysicalDevice();
	init_info.Device = m_context.getLogicalDevice();
	init_info.QueueFamily = m_context.getQueueFamilyIndices().graphicsFamily.value();
	init_info.Queue = m_context.getGraphicsQueue();
	init_info.PipelineCache = VK_NULL_HANDLE;
	init_info.DescriptorPool = m_descriptorPool;
	init_info.PipelineInfoMain.RenderPass = m_swapchain.getRenderPass();
	init_info.PipelineInfoMain.Subpass = 0;
	init_info.PipelineInfoMain.MSAASamples = m_context.getMsaaSamples();
	init_info.Allocator = nullptr;
	init_info.MinImageCount = 2;
	init_info.ImageCount = static_cast<uint32_t>(m_swapchain.getImageCount());
	init_info.CheckVkResultFn = nullptr;

	ImGui_ImplVulkan_Init(&init_info);
	m_isInitialized = true;
}

void	ImGuiGui::beginFrame() {
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void	ImGuiGui::endFrame() {
	ImGui::Render();
}

bool	ImGuiGui::beginWindow(const std::string& name, bool* open) {
	++m_windowDepth;
	return ImGui::Begin(name.c_str(), open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
}

void	ImGuiGui::endWindow() {
	if (m_windowDepth > 0)
		--m_windowDepth;
	ImGui::End();
}

bool	ImGuiGui::beginSection(const std::string& name, bool* open) {
	ImGui::PushID(name.c_str());
	(void)open;

	return ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_CollapsingHeader);
}

void	ImGuiGui::endSection() {
	ImGui::PopID();
}

void	ImGuiGui::text(const std::string& value) {
	ImGui::Text("%s", value.c_str());
}

bool	ImGuiGui::button(const std::string& label) {
	return ImGui::Button(label.c_str());
}

bool	ImGuiGui::wantsMouseCapture() const {
	return ImGui::GetIO().WantCaptureMouse;
}

bool	ImGuiGui::wantsKeyboardCapture() const {
	return ImGui::GetIO().WantCaptureKeyboard;
}

void	ImGuiGui::render(VkCommandBuffer commandBuffer) {
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

ImGuiGui::~ImGuiGui() {
	vkDeviceWaitIdle(m_context.getLogicalDevice());
	if (m_isInitialized) {
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}
	if (m_descriptorPool != VK_NULL_HANDLE)
		vkDestroyDescriptorPool(m_context.getLogicalDevice(), m_descriptorPool, nullptr);
	ImGui::DestroyContext(m_imguiContext);
}
