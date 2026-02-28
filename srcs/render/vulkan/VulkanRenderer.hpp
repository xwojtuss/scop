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
#include "../../platform/filesystem/readFile.hpp"
#include "../../ecs/system/SystemManager.hpp"

namespace render::vulkan {

constexpr const char*	fragShaderPath = "shaders/shader.frag.spv";
constexpr const char*	vertShaderPath = "shaders/shader.vert.spv";
constexpr const char*	textFragShaderPath = "shaders/fontShader.frag.spv";
constexpr const char*	textVertShaderPath = "shaders/fontShader.vert.spv";

const uint32_t	maxTextChars = 512;

constexpr const int	fontBitMapWidth = 16;
constexpr const int	fontBitMapHeight = 8;

class VulkanRenderer : public render::IRenderer {
private:
	std::unique_ptr<VulkanContext>			m_context;
	std::unique_ptr<VulkanSwapchain>		m_swapchain;
	std::unique_ptr<VulkanResourceManager>	m_resourceManager;
	std::unique_ptr<VulkanFrameData>		m_frameData;
	VkPipelineLayout						m_pipelineLayout;
	VkPipelineLayout						m_textPipelineLayout;
	VkPipeline								m_graphicsPipeline;
	VkPipeline								m_textPipeline;
	std::optional<uint32_t>					m_frameIndex;
	std::array<VkClearValue, 2>				m_clearValues;
	assets::MeshHandle						m_textMeshHandle;
	VkBuffer								m_instanceBuffer;
	VkDeviceMemory							m_instanceBufferMemory;

	void					createPipeline();
	void					createTextPipeline();
	VkShaderModule			createShaderModule(const std::vector<char>& code, VkDevice device);
	void					recordCurrentCommandBuffer(ecs::SystemManager& systemManager, uint32_t currentFrame);
	void					cleanup();
	void					createTextMesh();
	void					copyTextToInstanceBuffer(const std::string& text);
	
public:
	VulkanRenderer(platform::window::IWindow&);
	~VulkanRenderer() override;
	
	assets::MeshHandle			createMesh(const assets::MeshData&) override;
	assets::TextureHandle		createTexture(const assets::TextureData&) override;
	const assets::MeshHandle&	getTextMeshHandle() const;
	void						beginFrame() override;
	void						render(ecs::SystemManager& systemManager) override;
	void						endFrame() override;
	void						setClearColor(float r, float g, float b, float a) override;
	void						drawMesh(const assets::MeshHandle& mesh, const assets::TextureHandle& texture, const ecs::component::Transform& transform) override;
	void						drawText(const std::string& text, const assets::TextureHandle& font, const ecs::component::Transform2D& transform, const ecs::component::Color* color = nullptr) override;
	void						updateCamera(const component::Camera& camera) override;
};
}