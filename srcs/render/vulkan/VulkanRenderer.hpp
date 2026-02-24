#pragma once

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanContext.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanResourceManager.hpp"
#include "VulkanFrameData.hpp"
#include "VulkanValidationLayers.hpp"
#include "VulkanVertexUtils.hpp"
#include "../render/IRenderer.hpp"
#include "../../platform/window/IWindow.hpp"
#include "../../scene/Scene.hpp"
#include "../../platform/filesystem/readFile.hpp"

namespace render::vulkan {

constexpr const char*	fragShaderPath = "shaders/shader.frag.spv";
constexpr const char*	vertShaderPath = "shaders/shader.vert.spv";

class VulkanRenderer : public render::IRenderer {
private:
	std::unique_ptr<VulkanContext>			m_context;
	std::unique_ptr<VulkanSwapchain>		m_swapchain;
	std::unique_ptr<VulkanResourceManager>	m_resourceManager;
	std::unique_ptr<VulkanFrameData>		m_frameData;
	VkPipelineLayout						m_pipelineLayout;
	VkPipeline								m_graphicsPipeline;
	std::optional<uint32_t>					m_frameIndex;
	std::array<VkClearValue, 2>				m_clearValues;

	void					createPipeline();
	VkShaderModule			createShaderModule(const std::vector<char>& code, VkDevice device);
	void					recordCommandBuffer(VkCommandBuffer commandBuffer, std::vector<scene::Renderable>& renderables, uint32_t frameIndex);
	void					cleanup();

public:
	VulkanRenderer(platform::window::IWindow&);
	~VulkanRenderer() override;

	assets::MeshHandle		createMesh(const assets::MeshData&) override;
	assets::TextureHandle	createTexture(const assets::TextureData&) override;
	void					beginFrame() override;
	void					render(scene::Scene&) override;
	void					endFrame() override;
	void					setClearColor(float r, float g, float b, float a) override;
	
};
}