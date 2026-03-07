#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <unordered_map>
#include <vector>

#include "VulkanContext.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanResourceManager.hpp"
#include "VulkanFrameData.hpp"
#include "VulkanValidationLayers.hpp"
#include "VulkanVertexUtils.hpp"
#include "pipeline/TexturePipeline.hpp"
#include "pipeline/VertexColorPipeline.hpp"
#include "pipeline/TextPipeline.hpp"
#include "../render/IRenderer.hpp"
#include "../../platform/window/IWindow.hpp"
#include "../../platform/filesystem/readFile.hpp"
#include "../../ecs/system/SystemManager.hpp"

namespace render::vulkan {
const uint32_t	maxTextChars = 512;

constexpr const int	fontBitMapWidth = 16;
constexpr const int	fontBitMapHeight = 8;

class VulkanRenderer : public render::IRenderer {
private:
	std::unique_ptr<VulkanContext>											m_context;
	std::unique_ptr<VulkanSwapchain>										m_swapchain;
	std::unique_ptr<VulkanResourceManager>									m_resourceManager;
	std::unique_ptr<VulkanFrameData>										m_frameData;
	std::optional<uint32_t>													m_frameIndex;
	std::array<VkClearValue, 2>												m_clearValues;
	assets::MeshHandle														m_textMeshHandle;
	std::unordered_map<assets::PipelineType, std::unique_ptr<APipeline>>	m_pipelineHandles;
	VkBuffer																m_instanceBuffer;
	VkDeviceMemory															m_instanceBufferMemory;
	std::vector<VkSemaphore>									m_renderFinishedSemaphores;

	void					createPipelines();
	void					createRenderFinishedSemaphores();
	void					cleanupRenderFinishedSemaphores();
	VkShaderModule			createShaderModule(const std::vector<char>& code, VkDevice device);
	void					recordCurrentCommandBuffer(ecs::SystemManager& systemManager);
	void					cleanup() override;
	void					cleanupPipelines();
	void					createTextMesh();
	void					copyTextToInstanceBuffer(const std::string& text, size_t offset);
	
public:
	VulkanRenderer(platform::window::IWindow&);
	~VulkanRenderer() override;
	
	assets::MeshHandle			createMesh(const assets::MeshData&) override;
	assets::TextureHandle		createTexture(const assets::TextureData&) override;
	const assets::MeshHandle&	getTextMeshHandle() const override;
	void						beginFrame() override;
	void						render(ecs::SystemManager& systemManager) override;
	void						render(render::gui::IGui& gui) override;
	void						endFrame() override;
	void						setClearColor(float r, float g, float b, float a) override;
	void						setClearColor(int hexColor) override;
	void						drawMesh(const ecs::component::Mesh& mesh, const ecs::component::Texture* texture, const ecs::component::Transform& transform) override;
	void						drawText(const ecs::component::Text& text, const ecs::component::Texture* texture, const ecs::component::Transform2D& transform, size_t offset, const ecs::component::Color* color = nullptr) override;
	void						updateCamera(const component::Camera& camera) override;
	VulkanContext&				getContext();
	VulkanSwapchain&			getSwapchain();
	platform::window::IWindow&	getWindow();
};
}